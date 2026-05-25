#include "HistoryWidget.h"
#include "historystorage.h"
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>

HistoryWidget::HistoryWidget(QWidget* parent) : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    historyBox = new QTextEdit(this);
    historyBox->setReadOnly(true);
    historyBox->setPlaceholderText("Здесь будет история сгенерированных паролей...");
    clearButton = new QPushButton("Очистить историю", this);

    layout->addWidget(historyBox);
    layout->addWidget(clearButton);

    connect(clearButton, &QPushButton::clicked, this, &HistoryWidget::clearHistory);

    loadHistory();
}

void HistoryWidget::loadHistory()
{
    auto& storage = HistoryStorage::instance();
    storage.loadFromFile();
    for (const auto& pass : storage.getAll()) {
        historyBox->append(QString::fromStdString(pass));
    }
}

void HistoryWidget::addPassword(const QString& password)
{
    historyBox->append(password);
    HistoryStorage::instance().add(password.toStdString());
}

void HistoryWidget::clearHistory()
{
    historyBox->clear();
    HistoryStorage::instance().clear();
}