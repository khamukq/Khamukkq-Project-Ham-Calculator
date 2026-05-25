cmake_minimum_required(VERSION 3.16)

project(HamPassword)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Core Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Core Network)

set(SOURCES
    main.cpp
    mainwindow.cpp
    PasswordWidget.cpp
    HistoryWidget.cpp
    randomgenerator.cpp
    stdgenerator.cpp
    xamgenerator.cpp
    historystorage.cpp
    passwordutils.cpp
)

set(HEADERS
    mainwindow.h
    PasswordWidget.h
    HistoryWidget.h
    randomgenerator.h
    passwordgenerator.h
    stdgenerator.h
    xamgenerator.h
    historystorage.h
    passwordutils.h
)

add_executable(HamPassword ${SOURCES} ${HEADERS}
    PasswordWidgetStyles.h
    PasswordWidgetStyles.cpp
    PasswordWidgetUI.h
    PasswordWidgetUI.cpp
    LeakChecker.h
    LeakChecker.cpp)

target_link_libraries(HamPassword PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Network
)

target_include_directories(HamPassword PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})