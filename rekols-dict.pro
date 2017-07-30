#-------------------------------------------------
#
# Project created by QtCreator 2017-06-08T14:27:31
#
#-------------------------------------------------

QT  += core gui network multimedia x11extras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rekols-dict
TEMPLATE = app

CONFIG += link_pkgconfig
CONFIG += c++11
PKGCONFIG += dtkwidget xcb xcb-util

SOURCES += main.cpp\
    main_window.cpp \
    home_page.cpp \
    dict_page.cpp \
    tabbar.cpp \
    translator_page.cpp \
    youdao_api.cpp \
    load_page.cpp \
    data_page.cpp \
    event_monitor.cpp \
    click_box.cpp \
    float_box.cpp \
    settings.cpp \
    utils.cpp

HEADERS  += main_window.h \
    home_page.h \
    dict_page.h \
    tabbar.h \
    translator_page.h \
    youdao_api.h \
    load_page.h \
    data_page.h \
    event_monitor.h \
    click_box.h \
    float_box.h \
    settings.h \
    utils.h

RESOURCES = images.qrc

LIBS += -lX11 -lXext -lXtst

QMAKE_CXXFLAGS += -g

isEmpty(BINDIR):BINDIR=/usr/bin
isEmpty(APPDIR):APPDIR=/usr/share/applications

target.path = $$INSTROOT$$BINDIR
desktop.path = $$INSTROOT$$APPDIR
desktop.files = keyboard-sound.desktop

INSTALLS += target desktop
