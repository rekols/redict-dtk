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

#include "toolbar.h"
#include "utils.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QDebug>
#include <QEvent>
#include <QMouseEvent>

ToolBar::ToolBar(QWidget *parent)
    : QWidget(parent)
{
    QPixmap iconPixmap = Utils::renderSVG(":/images/redict.svg", QSize(22, 22));
    QLabel *iconLabel = new QLabel;
    iconLabel->setPixmap(iconPixmap);

    tabbar = new QTabBar;
    tabbar->addTab("词典");
    tabbar->addTab("翻译");
    tabbar->setFocusPolicy(Qt::NoFocus);
    tabbar->installEventFilter(this);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addSpacing(5);
    layout->addWidget(iconLabel);
    layout->addSpacing(5);
    layout->addWidget(tabbar);
    layout->addStretch();
    layout->setMargin(0);

    connect(tabbar, &QTabBar::currentChanged, this, [=] (int current) { emit currentChanged(current); });
}

ToolBar::~ToolBar()
{
}
