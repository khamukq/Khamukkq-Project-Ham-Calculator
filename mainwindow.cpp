#include "MainWindow.h"
#include "PasswordWidget.h"
#include "HistoryWidget.h"
#include <QTabWidget>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    setWindowTitle("Ham Password Generator");
    resize(700, 600);

    QTabWidget* tabs = new QTabWidget(this);
    setCentralWidget(tabs);

    PasswordWidget* passwordWidget = new PasswordWidget(this);
    HistoryWidget* historyWidget = new HistoryWidget(this);

    tabs->addTab(passwordWidget, "Генератор");
    tabs->addTab(historyWidget, "История");

    connect(passwordWidget, &PasswordWidget::passwordGenerated,
            historyWidget, &HistoryWidget::addPassword);
}