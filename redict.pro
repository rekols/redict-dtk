QT  += core gui network multimedia svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = redict
TEMPLATE = app
CONFIG += c++11 link_pkgconfig
PKGCONFIG += dtkwidget

SOURCES += main.cpp\
        main_window.cpp \
    toolbar.cpp \
    home_page.cpp \
    load_page.cpp \
    dict_page.cpp \
    youdao_api.cpp \
    settings.cpp

HEADERS  += main_window.h \
    toolbar.h \
    home_page.h \
    load_page.h \
    dict_page.h \
    youdao_api.h \
    settings.h

RESOURCES += resources.qrc

QMAKE_CXXFLAGS += -g

isEmpty(BINDIR):BINDIR=/usr/bin
isEmpty(APPDIR):APPDIR=/usr/share/applications

target.path = $$INSTROOT$$BINDIR
desktop.path = $$INSTROOT$$APPDIR
desktop.files = rekols-dict.desktop

INSTALLS += target desktop
