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
#include <QApplication>
#include <QClipboard>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent)
    : DMainWindow(parent),
      m_mainLayout(new QStackedLayout),
      m_toolBar(new ToolBar),
      m_popupWindow(new PopupWindow),
      m_homePage(new HomePage),
      m_trayIcon(new TrayIcon(this))
{
    QWidget *centralWidget = new QWidget;

    m_mainLayout->addWidget(m_homePage);

    titlebar()->setCustomWidget(m_toolBar, Qt::AlignVCenter, false);
    titlebar()->setBackgroundTransparent(true);
    titlebar()->setFixedHeight(30);

    m_trayIcon->show();

    centralWidget->setLayout(m_mainLayout);
    setCentralWidget(centralWidget);
    setWindowIcon(QIcon(":/images/redict.svg"));
    setShadowOffset(QPoint(0, 0));
    setFixedSize(550, 410);

    connect(qApp->clipboard(), &QClipboard::selectionChanged, [=] {
        m_popupWindow->query(qApp->clipboard()->text(QClipboard::Selection));
        m_popupWindow->popup(QCursor::pos());
    });

    connect(m_trayIcon, &TrayIcon::openActionTriggered, this, &MainWindow::activeWindow);
    connect(m_trayIcon, &TrayIcon::exitActionTriggered, qApp, &QApplication::quit);
}

MainWindow::~MainWindow()
{
    delete m_popupWindow;
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    setVisible(false);
    e->ignore();
}

void MainWindow::activeWindow()
{
    setVisible(!isVisible());

    if (isVisible()) {
        activateWindow();
    }
}
