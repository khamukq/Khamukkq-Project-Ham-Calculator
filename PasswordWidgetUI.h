#ifndef PASSWORDWIDGETUI_H
#define PASSWORDWIDGETUI_H

#include <QWidget>

class QLabel;
class QPushButton;
class QSlider;
class QProgressBar;
class QCheckBox;
class QComboBox;
class QGroupBox;
class QVBoxLayout;

class PasswordWidgetUI
{
public:
    explicit PasswordWidgetUI(QWidget* parent);
    void setupUI();

    // UI элементы
    QLabel* passwordLabel = nullptr;
    QLabel* lengthLabel = nullptr;
    QLabel* entropyLabel = nullptr;
    QLabel* leakLabel = nullptr;
    QSlider* slider = nullptr;
    QProgressBar* strengthBar = nullptr;
    QProgressBar* leakBar = nullptr;
    QCheckBox* uppercaseBox = nullptr;
    QCheckBox* digitsBox = nullptr;
    QCheckBox* symbolsBox = nullptr;
    QComboBox* modeBox = nullptr;
    QComboBox* langBox = nullptr;
    QPushButton* generateButton = nullptr;
    QPushButton* copyButton = nullptr;
    QPushButton* exportButton = nullptr;
    QPushButton* checkLeakButton = nullptr;

    // XAM настройки
    QWidget* xamSettingsWidget = nullptr;
    QSlider* xamWordsSlider = nullptr;
    QLabel* xamWordsValueLabel = nullptr;
    QCheckBox* xamHyphensCheckBox = nullptr;

private:
    QWidget* parent;
    QVBoxLayout* mainLayout;
    QGroupBox* createLengthGroup();
    QGroupBox* createXamGroup();
    QGroupBox* createSecurityGroup();
    QGroupBox* createCharGroup();
    QGroupBox* createModeGroup();
    QGroupBox* createLangGroup();
    void createButtons();
};

#endif