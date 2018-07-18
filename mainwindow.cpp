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

MainWindow::MainWindow(QWidget *parent)
    : DMainWindow(parent),
      m_mainLayout(new QStackedLayout),
      m_toolBar(new ToolBar),
      m_popupWindow(new PopupWindow),
      m_homePage(new HomePage),
      m_dictPage(new DictPage)
{
    QWidget *centralWidget = new QWidget;

    m_mainLayout->addWidget(m_homePage);
    m_mainLayout->addWidget(m_dictPage);

    titlebar()->setCustomWidget(m_toolBar, Qt::AlignVCenter, false);
    titlebar()->setBackgroundTransparent(true);
    titlebar()->setFixedHeight(45);

    centralWidget->setLayout(m_mainLayout);
    setCentralWidget(centralWidget);
    setShadowOffset(QPoint(0, 0));
    setFixedSize(550, 400);

    connect(qApp->clipboard(), &QClipboard::selectionChanged, [=] {
        m_popupWindow->query(qApp->clipboard()->text(QClipboard::Selection));
        m_popupWindow->popup(QCursor::pos());
    });

    connect(m_toolBar, &ToolBar::textChanged, this, [=] (const QString &text) {
                                                        if (text.isEmpty()) {
                                                            m_mainLayout->setCurrentIndex(0);
                                                        } else {
                                                            m_dictPage->queryWord(text);
                                                            m_mainLayout->setCurrentIndex(1);
                                                        }
                                                    });
}

MainWindow::~MainWindow()
{
    delete m_popupWindow;
}
