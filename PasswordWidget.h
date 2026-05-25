#ifndef PASSWORDWIDGET_H
#define PASSWORDWIDGET_H

#include <QWidget>
#include <QTranslator>
#include "PasswordWidgetUI.h"

class PasswordWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PasswordWidget(QWidget* parent = nullptr);

signals:
    void passwordGenerated(const QString& password);

private slots:
    void onGenerate();
    void onCopy();
    void onExport();
    void onModeChanged(const QString& mode);
    void onCheckLeak();
    void changeLanguage(int index);
    void onLeakResult(const QString& result, bool isSafe);

private:
    void setupConnections();
    void animateWidget(QWidget* widget);
    void updateLanguage();

    PasswordWidgetUI* ui;
    QTranslator translator;
    QString currentPassword;
};

#endif