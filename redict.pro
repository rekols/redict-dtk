QT += core gui svg network multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = redict
TEMPLATE = app
CONFIG += c++11 link_pkgconfig
PKGCONFIG += dtkwidget

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp \
        mainwindow.cpp \
	toolbar.cpp \
	utils.cpp \
	homepage.cpp \
	infopage.cpp \
	dictpage.cpp

HEADERS += \
        mainwindow.h \
	toolbar.h \
	utils.h \
	homepage.h \
	infopage.h \
	dictpage.h

RESOURCES += \
    redict.qrc
