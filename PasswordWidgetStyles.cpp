#include "PasswordWidgetStyles.h"

QString PasswordWidgetStyles::getMainStyle()
{
    return "QWidget { background-color: #0a0a0a; color: #e0e0e0; font-family: 'Segoe UI'; }"
           "QGroupBox { font-weight: bold; border: 1px solid #2a2a2a; border-radius: 8px; margin-top: 12px; padding-top: 8px; background-color: #0d0d0d; }"
           "QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 5px; color: #cccccc; }"
           "QLabel { color: #cccccc; }"
           "QCheckBox { spacing: 8px; color: #cccccc; margin: 5px; }"
           "QCheckBox::indicator { width: 18px; height: 18px; border-radius: 4px; border: 1px solid #555; background-color: #1a1a1a; }"
           "QCheckBox::indicator:checked { background-color: #0078D4; border: 1px solid #0078D4; }"
           "QComboBox { padding: 6px; border: 1px solid #333; border-radius: 6px; background-color: #1a1a1a; color: #e0e0e0; }"
           "QComboBox:hover { border-color: #0078D4; }";
}

QString PasswordWidgetStyles::getPasswordLabelStyle()
{
    return "background-color: #0d0d0d; color: #0078D4; border-radius: 12px; padding: 20px; "
           "font-size: 20px; font-weight: bold; font-family: 'Courier New', monospace; border: 1px solid #2a2a2a;";
}

QString PasswordWidgetStyles::getButtonStyle(const QString& color)
{
    return "QPushButton { border: none; padding: 10px; border-radius: 6px; font-weight: bold; background-color: " + color + "; color: #e0e0e0; }"
                                                                                                                            "QPushButton:hover { background-color: #252525; }"
                                                                                                                            "QPushButton:pressed { background-color: #0078D4; }";
}

QString PasswordWidgetStyles::getSliderStyle()
{
    return "QSlider::groove:horizontal { height: 4px; background: #2a2a2a; border-radius: 2px; }"
           "QSlider::handle:horizontal { background: #0078D4; width: 16px; height: 16px; margin: -6px 0; border-radius: 8px; }"
           "QSlider::handle:horizontal:hover { background: #0090f0; }"
           "QSlider::sub-page:horizontal { background: #0078D4; border-radius: 2px; }";
}

QString PasswordWidgetStyles::getProgressBarStyle()
{
    return "QProgressBar { border: 1px solid #2a2a2a; border-radius: 4px; text-align: center; background-color: #1a1a1a; color: #e0e0e0; }"
           "QProgressBar::chunk { background-color: #0078D4; border-radius: 3px; }";
}

QString PasswordWidgetStyles::getLeakButtonStyle()
{
    return "QPushButton { background-color: #1a1a1a; border: 1px solid #FF9800; color: #FF9800; border-radius: 6px; padding: 8px; }"
           "QPushButton:hover { background-color: #252525; border-color: #FFB74D; }"
           "QPushButton:pressed { background-color: #FF9800; color: #1a1a1a; }";
}

QString PasswordWidgetStyles::getDarkTheme()
{
    return getMainStyle() + getSliderStyle() + getProgressBarStyle();
}