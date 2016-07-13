QT = core gui widgets

TARGET = PaletteAnalyzer
TEMPLATE = app

CONFIG += c++14

mac* | linux*{
	CONFIG(release, debug|release):CONFIG += Release
	CONFIG(debug, debug|release):CONFIG += Debug
}

Release:OUTPUT_DIR=release
Debug:OUTPUT_DIR=debug

DESTDIR  = bin/$${OUTPUT_DIR}
OBJECTS_DIR = build/$${OUTPUT_DIR}/app
MOC_DIR     = build/$${OUTPUT_DIR}/app
UI_DIR      = build/$${OUTPUT_DIR}/app
RCC_DIR     = build/$${OUTPUT_DIR}/app

win*{
	QMAKE_CXXFLAGS += /MP /wd4251
	QMAKE_CXXFLAGS_WARN_ON = /W4
	DEFINES += WIN32_LEAN_AND_MEAN NOMINMAX _SCL_SECURE_NO_WARNINGS
}

linux*|mac*{

	QMAKE_CXXFLAGS_WARN_ON = -Wall -Wno-c++11-extensions -Wno-local-type-template-args -Wno-deprecated-register

	CONFIG(release, debug|release):CONFIG += Release
	CONFIG(debug, debug|release):CONFIG += Debug

	Release:DEFINES += NDEBUG=1
	Debug:DEFINES += _DEBUG
}

win32*:!*msvc2012:*msvc* {
	QMAKE_CXXFLAGS += /FS
}

SOURCES += \
	app/src/main.cpp \
	app/src/mainwindow.cpp

HEADERS += \
	app/src/mainwindow.h \
	app/src/rgb2lab.h

FORMS += \
	app/src/mainwindow.ui
