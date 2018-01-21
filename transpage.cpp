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

#include "transpage.h"

TransPage::TransPage(QWidget *parent)
    : QWidget(parent),
      m_layout(new QVBoxLayout(this)),
      m_originEdit(new QTextEdit),
      m_transEdit(new QTextEdit),
      m_transButton(new QPushButton("翻译"))
{
    m_originEdit->setObjectName("TransEdit");
    m_transEdit->setObjectName("TransEdit");
    m_transEdit->setReadOnly(true);

    m_layout->addWidget(m_originEdit);
    m_layout->addWidget(m_transButton);
    m_layout->addWidget(m_transEdit);
}

TransPage::~TransPage()
{
}
