/*
 * Copyright (C) 2017 ~ 2017 Deepin Technology Co., Ltd.
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

#include "dictpage.h"

DictPage::DictPage(QWidget *parent)
    : QWidget(parent),
      m_contentFrame(new QWidget),
      m_contentLayout(new QVBoxLayout(m_contentFrame)),
      m_contentArea(new QScrollArea),
      m_api(new YoudaoAPI)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_contentArea);

    m_contentArea->setContentsMargins(0, 0, 0, 0);
    m_contentArea->setWidgetResizable(true);
    m_contentArea->setWidget(m_contentFrame);
}

DictPage::~DictPage()
{
}
