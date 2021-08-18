CONFIG += console

TEMPLATE = app
TARGET = monitor_lighting

QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
	src/main.cpp \
	src/mainwindow.cpp \
	src/serial.cpp

HEADERS += \
	src/mainwindow.h \
	src/serial.h

RESOURCES += \
	Resources.qrc
