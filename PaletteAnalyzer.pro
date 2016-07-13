QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PaletteAnalyzer
TEMPLATE = app


SOURCES += \
	app/src/main.cpp \
    app/src/mainwindow.cpp

HEADERS += \
	app/src/mainwindow.h \
    app/src/rgb2lab.h

FORMS += \
	app/src/mainwindow.ui
