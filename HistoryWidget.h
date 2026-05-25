#ifndef HISTORYWIDGET_H
#define HISTORYWIDGET_H

#include <QWidget>

class QTextEdit;
class QPushButton;

class HistoryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HistoryWidget(QWidget* parent = nullptr);

public slots:
    void addPassword(const QString& password);
    void clearHistory();

private:
    void loadHistory();

    QTextEdit* historyBox = nullptr;
    QPushButton* clearButton = nullptr;
};

#endif