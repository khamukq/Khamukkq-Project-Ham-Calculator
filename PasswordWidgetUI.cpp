#include "PasswordWidgetUI.h"
#include "PasswordWidgetStyles.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QProgressBar>
#include <QCheckBox>
#include <QComboBox>
#include <QGroupBox>

PasswordWidgetUI::PasswordWidgetUI(QWidget* parent) : parent(parent)
{
    mainLayout = new QVBoxLayout(parent);
    mainLayout->setSpacing(15);
    mainLayout->setContentsMargins(25, 25, 25, 25);
}

void PasswordWidgetUI::setupUI()
{
    // Поле для пароля
    passwordLabel = new QLabel("⚡ НАЖМИТЕ \"СГЕНЕРИРОВАТЬ\" ⚡", parent);
    passwordLabel->setAlignment(Qt::AlignCenter);
    passwordLabel->setMinimumHeight(100);
    QFont passwordFont = passwordLabel->font();
    passwordFont.setPointSize(20);
    passwordFont.setBold(true);
    passwordLabel->setFont(passwordFont);
    passwordLabel->setStyleSheet(PasswordWidgetStyles::getPasswordLabelStyle());
    mainLayout->addWidget(passwordLabel);

    mainLayout->addWidget(createLengthGroup());
    mainLayout->addWidget(createXamGroup());
    mainLayout->addWidget(createSecurityGroup());
    mainLayout->addWidget(createCharGroup());
    mainLayout->addWidget(createModeGroup());
    createButtons();
    mainLayout->addWidget(createLangGroup());
    mainLayout->addStretch();
}

QGroupBox* PasswordWidgetUI::createLengthGroup()
{
    QGroupBox* group = new QGroupBox("⚙️ ДЛИНА ПАРОЛЯ", parent);
    QVBoxLayout* layout = new QVBoxLayout(group);

    lengthLabel = new QLabel("12 символов", parent);
    lengthLabel->setAlignment(Qt::AlignCenter);
    lengthLabel->setStyleSheet("font-size: 13px; font-weight: bold; color: #888;");

    slider = new QSlider(Qt::Horizontal, parent);
    slider->setRange(4, 32);
    slider->setValue(12);
    slider->setTickPosition(QSlider::TicksBelow);
    slider->setTickInterval(4);
    slider->setStyleSheet(PasswordWidgetStyles::getSliderStyle());

    layout->addWidget(lengthLabel);
    layout->addWidget(slider);
    return group;
}

QGroupBox* PasswordWidgetUI::createXamGroup()
{
    xamSettingsWidget = new QWidget(parent);
    QVBoxLayout* xamMainLayout = new QVBoxLayout(xamSettingsWidget);

    QGroupBox* group = new QGroupBox("📖 XAM НАСТРОЙКИ", parent);
    QVBoxLayout* groupLayout = new QVBoxLayout(group);

    QHBoxLayout* wordsLayout = new QHBoxLayout;
    QLabel* wordsLabel = new QLabel("Количество слов:", parent);
    wordsLabel->setStyleSheet("font-weight: bold;");

    xamWordsSlider = new QSlider(Qt::Horizontal, parent);
    xamWordsSlider->setRange(2, 6);
    xamWordsSlider->setValue(3);
    xamWordsSlider->setTickPosition(QSlider::TicksBelow);
    xamWordsSlider->setTickInterval(1);

    xamWordsValueLabel = new QLabel("3", parent);
    xamWordsValueLabel->setMinimumWidth(30);
    xamWordsValueLabel->setStyleSheet("font-weight: bold; color: #0078D4;");

    wordsLayout->addWidget(wordsLabel);
    wordsLayout->addWidget(xamWordsSlider);
    wordsLayout->addWidget(xamWordsValueLabel);
    groupLayout->addLayout(wordsLayout);

    xamHyphensCheckBox = new QCheckBox("Использовать разделители (дефисы или пробелы)", parent);
    xamHyphensCheckBox->setChecked(true);
    groupLayout->addWidget(xamHyphensCheckBox);

    xamMainLayout->addWidget(group);
    xamSettingsWidget->setVisible(false);
    return group;
}

QGroupBox* PasswordWidgetUI::createSecurityGroup()
{
    QGroupBox* group = new QGroupBox("🔒 БЕЗОПАСНОСТЬ", parent);
    QVBoxLayout* layout = new QVBoxLayout(group);

    QHBoxLayout* entropyLayout = new QHBoxLayout;
    QLabel* entropyTitle = new QLabel("Энтропия:", parent);
    entropyTitle->setStyleSheet("font-weight: bold;");

    entropyLabel = new QLabel("0 бит", parent);
    entropyLabel->setStyleSheet("color: #0078D4; font-weight: bold;");

    strengthBar = new QProgressBar(parent);
    strengthBar->setRange(0, 100);
    strengthBar->setFormat("%v%");
    strengthBar->setStyleSheet(PasswordWidgetStyles::getProgressBarStyle());

    entropyLayout->addWidget(entropyTitle);
    entropyLayout->addWidget(entropyLabel);
    entropyLayout->addStretch();

    layout->addLayout(entropyLayout);
    layout->addWidget(strengthBar);
    return group;
}

QGroupBox* PasswordWidgetUI::createCharGroup()
{
    QGroupBox* group = new QGroupBox("🔤 НАБОР СИМВОЛОВ", parent);
    QVBoxLayout* layout = new QVBoxLayout(group);

    uppercaseBox = new QCheckBox("Заглавные буквы (A-Z)", parent);
    digitsBox = new QCheckBox("Цифры (0-9)", parent);
    symbolsBox = new QCheckBox("Специальные символы (!@#$%^&*)", parent);

    uppercaseBox->setChecked(true);
    digitsBox->setChecked(true);
    symbolsBox->setChecked(true);

    layout->addWidget(uppercaseBox);
    layout->addWidget(digitsBox);
    layout->addWidget(symbolsBox);
    return group;
}

QGroupBox* PasswordWidgetUI::createModeGroup()
{
    QGroupBox* group = new QGroupBox("🎮 РЕЖИМ ГЕНЕРАЦИИ", parent);
    QHBoxLayout* layout = new QHBoxLayout(group);

    modeBox = new QComboBox(parent);
    modeBox->addItem("Standard (случайные символы)");
    modeBox->addItem("XAM (слова из словаря)");
    layout->addWidget(modeBox);
    return group;
}

QGroupBox* PasswordWidgetUI::createLangGroup()
{
    QGroupBox* group = new QGroupBox("🌐 ЯЗЫК / LANGUAGE", parent);
    QHBoxLayout* layout = new QHBoxLayout(group);

    langBox = new QComboBox(parent);
    langBox->addItem("Русский");
    langBox->addItem("English");
    langBox->setMinimumWidth(100);

    QLabel* leakStatusLabel = new QLabel("Утечки:", parent);
    leakLabel = new QLabel("Не проверен", parent);
    leakLabel->setStyleSheet("color: #888;");
    leakLabel->setMinimumWidth(120);

    leakBar = new QProgressBar(parent);
    leakBar->setRange(0, 100);
    leakBar->setVisible(false);
    leakBar->setFixedWidth(80);

    checkLeakButton = new QPushButton("ПРОВЕРИТЬ НА УТЕЧКИ", parent);
    checkLeakButton->setMinimumHeight(35);
    checkLeakButton->setStyleSheet(PasswordWidgetStyles::getLeakButtonStyle());

    layout->addWidget(langBox);
    layout->addWidget(leakStatusLabel);
    layout->addWidget(leakLabel);
    layout->addWidget(leakBar);
    layout->addWidget(checkLeakButton);
    layout->addStretch();
    return group;
}

void PasswordWidgetUI::createButtons()
{
    QHBoxLayout* buttonLayout = new QHBoxLayout;

    generateButton = new QPushButton("СГЕНЕРИРОВАТЬ", parent);
    copyButton = new QPushButton("КОПИРОВАТЬ", parent);
    exportButton = new QPushButton("ЭКСПОРТ JSON", parent);

    for (auto* btn : {generateButton, copyButton, exportButton}) {
        btn->setMinimumHeight(40);
        btn->setStyleSheet(PasswordWidgetStyles::getButtonStyle());
    }

    buttonLayout->addWidget(generateButton);
    buttonLayout->addWidget(copyButton);
    buttonLayout->addWidget(exportButton);
    mainLayout->addLayout(buttonLayout);
}