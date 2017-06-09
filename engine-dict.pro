#-------------------------------------------------
#
# Project created by QtCreator 2017-06-08T14:27:31
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = engine-dict
TEMPLATE = app

CONFIG += link_pkgconfig
CONFIG += c++11
PKGCONFIG += dtkwidget dtkbase dtkutil

SOURCES += main.cpp\
        main_window.cpp \
    toolbar.cpp \
    home_page.cpp \
    loading_page.cpp \
    dict_page.cpp \
    load_progress.cpp

HEADERS  += main_window.h \
    toolbar.h \
    home_page.h \
    loading_page.h \
    dict_page.h \
    load_progress.h

RESOURCES = engine-dict.qrc
