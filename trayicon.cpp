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

#include "trayicon.h"
#include "mainwindow.h"

TrayIcon::TrayIcon(QObject *parent)
    : QSystemTrayIcon(parent),
      m_menu(new QMenu),
      m_openAction(new QAction(tr("打开"), m_menu)),
      m_exitAction(new QAction(tr("退出"), m_menu))
{
    m_menu->addAction(m_openAction);
    m_menu->addAction(m_exitAction);

    setContextMenu(m_menu);
    setIcon(QIcon(":/images/redict.svg"));
    setToolTip(tr("Redict"));

    connect(this, &QSystemTrayIcon::activated, this, &TrayIcon::iconActive);
    connect(m_openAction, &QAction::triggered, this, &TrayIcon::openActionTriggered);
    connect(m_exitAction, &QAction::triggered, this, &TrayIcon::exitActionTriggered);
}

TrayIcon::~TrayIcon()
{
    delete m_menu;
}

void TrayIcon::iconActive(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Context) {
        m_menu->show();        
    } else if (reason == QSystemTrayIcon::Trigger || reason == QSystemTrayIcon::DoubleClick) {
        Q_EMIT openActionTriggered();
    }
}
