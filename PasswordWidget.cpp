#include "PasswordWidget.h"
#include "PasswordWidgetStyles.h"
#include "stdgenerator.h"
#include "xamgenerator.h"
#include "passwordutils.h"
#include "LeakChecker.h"
#include <QClipboard>
#include <QGuiApplication>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QTimer>
#include <QSlider>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>
#include <QComboBox>
#include <QProgressBar>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMessageBox>

PasswordWidget::PasswordWidget(QWidget* parent) : QWidget(parent)
{
    ui = new PasswordWidgetUI(this);
    ui->setupUI();
    this->setStyleSheet(PasswordWidgetStyles::getDarkTheme());
    setupConnections();
    connect(&LeakChecker::instance(), &LeakChecker::resultReady,
            this, &PasswordWidget::onLeakResult);
}

void PasswordWidget::animateWidget(QWidget* widget)
{
    QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect();
    widget->setGraphicsEffect(effect);
    QPropertyAnimation* animation = new QPropertyAnimation(effect, "opacity");
    animation->setDuration(200);
    animation->setStartValue(0.3);
    animation->setEndValue(1.0);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void PasswordWidget::setupConnections()
{
    connect(ui->slider, &QSlider::valueChanged, this, [this](int v) {
        ui->lengthLabel->setText(QString::number(v) + " символов");
        animateWidget(ui->lengthLabel);
    });
    connect(ui->xamWordsSlider, &QSlider::valueChanged, this, [this](int v) {
        ui->xamWordsValueLabel->setText(QString::number(v));
        animateWidget(ui->xamWordsValueLabel);
    });
    connect(ui->modeBox, &QComboBox::currentTextChanged, this, &PasswordWidget::onModeChanged);
    connect(ui->generateButton, &QPushButton::clicked, this, &PasswordWidget::onGenerate);
    connect(ui->copyButton, &QPushButton::clicked, this, &PasswordWidget::onCopy);
    connect(ui->exportButton, &QPushButton::clicked, this, &PasswordWidget::onExport);
    connect(ui->langBox, &QComboBox::currentIndexChanged, this, &PasswordWidget::changeLanguage);
    connect(ui->checkLeakButton, &QPushButton::clicked, this, &PasswordWidget::onCheckLeak);
}

void PasswordWidget::onModeChanged(const QString& mode)
{
    bool isXam = mode.contains("XAM");
    ui->slider->parentWidget()->setVisible(!isXam);
    ui->xamSettingsWidget->setVisible(isXam);
}

void PasswordWidget::onGenerate()
{
    GeneratorParams params;
    params.useUppercase = ui->uppercaseBox->isChecked();
    params.useDigits = ui->digitsBox->isChecked();
    params.useSymbols = ui->symbolsBox->isChecked();

    std::string password;
    if (ui->modeBox->currentText().contains("XAM")) {
        params.wordCount = ui->xamWordsSlider->value();
        params.useHyphens = ui->xamHyphensCheckBox->isChecked();
        XamGenerator gen;
        password = gen.generate(params);
    } else {
        params.length = ui->slider->value();
        StandardGenerator gen;
        password = gen.generate(params);
    }

    animateWidget(ui->passwordLabel);
    QString qpassword = QString::fromStdString(password);
    ui->passwordLabel->setText(qpassword);
    currentPassword = qpassword;
    emit passwordGenerated(qpassword);

    double e = entropy(password.length(), params.useUppercase, params.useDigits, params.useSymbols);
    ui->entropyLabel->setText(QString::number(e, 'f', 1) + " бит");
    ui->strengthBar->setValue(strength(e));
    animateWidget(ui->entropyLabel);
    animateWidget(ui->strengthBar);
}

void PasswordWidget::onCopy()
{
    QGuiApplication::clipboard()->setText(ui->passwordLabel->text());
    ui->copyButton->setText("✓ СКОПИРОВАНО!");
    QTimer::singleShot(1500, [this]() { ui->copyButton->setText("КОПИРОВАТЬ"); });
    animateWidget(ui->copyButton);
}

void PasswordWidget::onExport()
{
    QJsonObject obj;
    obj["password"] = ui->passwordLabel->text();
    obj["length"] = ui->slider->value();
    obj["mode"] = ui->modeBox->currentText();
    obj["uppercase"] = ui->uppercaseBox->isChecked();
    obj["digits"] = ui->digitsBox->isChecked();
    obj["symbols"] = ui->symbolsBox->isChecked();

    QFile file("password_export.json");
    if (file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(obj).toJson());
        ui->exportButton->setText("✓ ЭКСПОРТИРОВАНО!");
        QTimer::singleShot(1500, [this]() { ui->exportButton->setText("ЭКСПОРТ JSON"); });
        animateWidget(ui->exportButton);
    }
}

void PasswordWidget::changeLanguage(int index)
{
    QString langFile = (index == 0) ? ":/translations/HamPassword_ru.qm" : ":/translations/HamPassword_en.qm";
    if (translator.load(langFile)) {
        qApp->installTranslator(&translator);
        updateLanguage();
    }
}

void PasswordWidget::updateLanguage()
{
    // Обновление текстов (упрощённо)
    ui->uppercaseBox->setText(tr("Заглавные буквы (A-Z)"));
    ui->digitsBox->setText(tr("Цифры (0-9)"));
    ui->symbolsBox->setText(tr("Специальные символы (!@#$%^&*)"));
    ui->modeBox->setItemText(0, tr("Standard (случайные символы)"));
    ui->modeBox->setItemText(1, tr("XAM (слова из словаря)"));
    ui->generateButton->setText(tr("СГЕНЕРИРОВАТЬ"));
    ui->copyButton->setText(tr("КОПИРОВАТЬ"));
    ui->exportButton->setText(tr("ЭКСПОРТ JSON"));
    ui->checkLeakButton->setText(tr("ПРОВЕРИТЬ НА УТЕЧКИ"));
    ui->xamHyphensCheckBox->setText(tr("Использовать разделители (дефисы или пробелы)"));
    ui->lengthLabel->setText(tr("%1 символов").arg(ui->slider->value()));
}

void PasswordWidget::onCheckLeak()
{
    if (currentPassword.isEmpty() || currentPassword.contains("НАЖМИТЕ")) {
        ui->leakLabel->setText(tr("Сначала сгенерируйте пароль"));
        ui->leakLabel->setStyleSheet("color: #FF9800;");
        return;
    }
    ui->leakLabel->setText(tr("Проверка..."));
    ui->leakLabel->setStyleSheet("color: #888;");
    ui->leakBar->setVisible(true);
    ui->leakBar->setRange(0, 0);

    LeakChecker::instance().check(currentPassword);
}

void PasswordWidget::onLeakResult(const QString& result, bool isSafe)
{
    ui->leakLabel->setText(result);
    ui->leakLabel->setStyleSheet(isSafe ? "color: #4CAF50; font-weight: bold;" : "color: #FF4444; font-weight: bold;");
    ui->leakBar->setVisible(false);
}