 🔐 Ham Password Generator

[![Build Status](https://github.com/khamukq/Khamukkq-Project-Ham-Calculator/actions/new)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
[![C++](https://img.shields.io/badge/C++-17-blue.svg)](https://isocpp.org/)
[![Qt](https://img.shields.io/badge/Qt-6-green.svg)](https://www.qt.io/)

> Генератор паролей с характером. Тёмная тема, проверка на утечки, два режима генерации и русский/английский интерфейс.

 ✨ Возможности

| Режим | Описание |
|-------|----------|
| 🎲 **Standard** | Случайные символы (буквы, цифры, спецсимволы) |
| 📖 **XAM** | Осмысленные слова из словаря + цифры |

### 🔒 Безопасность
- Проверка пароля через [HaveIBeenPwned](https://haveibeenpwned.com/API/v3) API
- Расчёт энтропии (бит)
- Шкала сложности пароля

### 🎨 Интерфейс
- Тёмная тема с анимациями
- Переключение на русский/английский
- Копирование в буфер обмена
- История паролей с экспортом в JSON

## 🖼️ Скриншоты

![Главное окно](screenshots/main.png)
![Проверка утечек](screenshots/leak_check.png)

## 🛠️ Технологии

- **C++17** (умные указатели, move-семантика)
- **Qt6** (Widgets, Network, Linguist)
- **CMake** (сборка)
- **Google Test** (юнит-тесты)
- **GitHub Actions** (CI/CD)

## 📦 Сборка

```bash
git clone https://github.com/ваш_ник/HamPassword.git
cd HamPassword
mkdir build && cd build
cmake ..
make
./HamPassword
