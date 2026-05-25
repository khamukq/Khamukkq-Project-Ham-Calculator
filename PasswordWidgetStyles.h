#ifndef PASSWORDWIDGETSTYLES_H
#define PASSWORDWIDGETSTYLES_H

#include <QString>

namespace PasswordWidgetStyles {
QString getMainStyle();
QString getPasswordLabelStyle();
QString getButtonStyle(const QString& color = "#1a1a1a");
QString getSliderStyle();
QString getProgressBarStyle();
QString getLeakButtonStyle();
QString getDarkTheme();
}

#endif