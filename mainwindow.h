/*
 * Copyright (C) 2017 ~ 2018 Deepin Technology Co., Ltd.
 *
 * Author:     rekols <rekols@foxmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <DMainWindow>
#include <QStackedLayout>
#include <QSettings>
#include <QMenu>

#include "toolbar.h"
#include "popupwindow.h"
#include "homepage.h"
#include "transpage.h"
#include "trayicon.h"
#include "eventmonitor.h"

DWIDGET_USE_NAMESPACE

class MainWindow : public DMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *);

private:
    void activeWindow();
    void initWordingAction();
    void initTrayIconAction();
    void initThemeAction();
    void enableWording();
    void disableWording();
    void handleWordingTriggered();
    void handleTrayIconTriggered();
    void handleThemeTriggered();

private:
    QStackedLayout *m_mainLayout;
    ToolBar *m_toolBar;
    EventMonitor *m_eventMonitor;
    PopupWindow *m_popupWindow;
    HomePage *m_homePage;
    TransPage *m_transPage;
    TrayIcon *m_trayIcon;
    QSettings *m_settings;
    QMenu *m_menu;
    QAction *m_wordingAction;
    QAction *m_trayIconAction;
    QAction *m_themeAction;
    bool m_enableWording;
    bool m_enableTrayIcon;
};

#endif
