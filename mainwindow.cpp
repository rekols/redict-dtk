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

#include "mainwindow.h"
#include "youdaoapi.h"
#include "dtitlebar.h"
#include "dthememanager.h"
#include "utils.h"

#include <QApplication>
#include <QClipboard>
#include <QCloseEvent>
#include <QKeyEvent>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : DMainWindow(parent),
      m_mainLayout(new QStackedLayout),
      m_toolBar(new ToolBar),
      m_eventMonitor(new EventMonitor),
      m_popupWindow(new PopupWindow),
      m_homePage(new HomePage),
      m_transPage(new TransPage),
      m_trayIcon(new TrayIcon(this)),
      m_settings(new QSettings("deepin", "redict")),
      m_menu(new QMenu),
      m_wordingAction(new QAction("划词翻译")),
      m_trayIconAction(new QAction("托盘显示")),
      m_themeAction(new QAction("暗色主题"))
{
    titlebar()->setCustomWidget(m_toolBar, Qt::AlignVCenter, false);
    titlebar()->setSeparatorVisible(true);
    titlebar()->setBackgroundTransparent(true);
    titlebar()->setFixedHeight(40);
    titlebar()->setMenu(m_menu);

    // init settings.
    if (!m_settings->contains("darkTheme")) {
        m_settings->setValue("darkTheme", false);
    }

    // init central widget.
    QWidget *centralWidget = new QWidget;
    m_mainLayout->addWidget(m_homePage);
    m_mainLayout->addWidget(m_transPage);

    centralWidget->setLayout(m_mainLayout);
    setWindowIcon(QIcon(":/images/redict.svg"));
    setCentralWidget(centralWidget);
    setShadowOffset(QPoint(0, 0));
    setFixedSize(550, 428);

    m_wordingAction->setCheckable(true);
    m_trayIconAction->setCheckable(true);
    m_themeAction->setCheckable(true);

    initWordingAction();
    initTrayIconAction();
    initThemeAction();

    m_menu->addAction(m_trayIconAction);
    m_menu->addAction(m_wordingAction);
    m_menu->addAction(m_themeAction);

    connect(m_trayIcon, &TrayIcon::openActionTriggered, this, &MainWindow::activeWindow);
    connect(m_trayIcon, &TrayIcon::exitActionTriggered, qApp, &QApplication::quit);
    connect(m_wordingAction, &QAction::triggered, this, &MainWindow::handleWordingTriggered);
    connect(m_trayIconAction, &QAction::triggered, this, &MainWindow::handleTrayIconTriggered);
    connect(m_themeAction, &QAction::triggered, this, &MainWindow::handleThemeTriggered);
    connect(m_toolBar, &ToolBar::currentChanged, m_mainLayout, &QStackedLayout::setCurrentIndex);
    connect(this, &MainWindow::requestKeyPressEvent, this, &MainWindow::keyPressEvent);
}

MainWindow::~MainWindow()
{
    delete m_popupWindow;
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    if (m_enableTrayIcon) {
        setVisible(false);
        e->ignore();
    } else {
        e->accept();
    }
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if (e->modifiers() == Qt::ControlModifier &&
        e->key() == Qt::Key_Tab) {

        const int tabCount = m_toolBar->tabbar->count();
        int tabIndex = m_toolBar->tabbar->currentIndex() + 1;

        if (tabIndex >= tabCount) {
            tabIndex = 0;
        }

        m_toolBar->tabbar->setCurrentIndex(tabIndex);
    }
}

void MainWindow::activeWindow()
{
    setVisible(!isVisible());

    if (isVisible()) {
        activateWindow();
    }
}

void MainWindow::initWordingAction()
{
    m_enableWording = m_settings->value("wording").toBool();

    if (m_enableWording) {
        m_wordingAction->setChecked(true);
        enableWording();
    } else {
        m_wordingAction->setChecked(false);
    }
}

void MainWindow::initTrayIconAction()
{
    m_enableTrayIcon = m_settings->value("tray").toBool();

    if (m_enableTrayIcon) {
        m_trayIconAction->setChecked(true);
        m_trayIcon->show();
    } else {
        m_trayIconAction->setChecked(false);
        m_trayIcon->hide();
    }
}

void MainWindow::initThemeAction()
{
    bool isDark = m_settings->value("darkTheme").toBool();

    if (isDark) {
        m_themeAction->setChecked(true);
        DThemeManager::instance()->setTheme("dark");
        setStyleSheet(Utils::getQssContent(":/qss/dark.qss"));
    } else {
        m_themeAction->setChecked(false);
        DThemeManager::instance()->setTheme("light");
        setStyleSheet(Utils::getQssContent(":/qss/light.qss"));
    }
}

void MainWindow::enableWording()
{
    // Windows and MacOS not support.
    connect(qApp->clipboard(), &QClipboard::selectionChanged, [=] {
        m_popupWindow->popup(QCursor::pos());
        m_popupWindow->query(qApp->clipboard()->text(QClipboard::Selection));
    });

    m_settings->setValue("wording", true);
    m_enableWording = true;
}

void MainWindow::disableWording()
{
    qApp->clipboard()->disconnect();

    m_settings->setValue("wording", false);
    m_enableWording = false;
}

void MainWindow::handleWordingTriggered()
{
    if (m_enableWording) {
        disableWording();
    } else {
        enableWording();
    }

    initWordingAction();
}

void MainWindow::handleTrayIconTriggered()
{
    if (m_enableTrayIcon) {
        m_enableTrayIcon = false;
        m_settings->setValue("tray", false);
        m_trayIcon->hide();
    } else {
        m_enableTrayIcon = true;
        m_settings->setValue("tray", true);
        m_trayIcon->show();
    }

    initTrayIconAction();
}

void MainWindow::handleThemeTriggered()
{
    bool isDark = m_settings->value("darkTheme").toBool();

    if (isDark) {
        m_settings->setValue("darkTheme", false);
    } else {
        m_settings->setValue("darkTheme", true);
    }

    initThemeAction();
}
