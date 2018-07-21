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

#include "homepage.h"
#include <QLineEdit>

HomePage::HomePage(QWidget *parent)
    : QWidget(parent),
      m_layout(new QStackedLayout),
      m_dailyPage(new DailyPage),
      m_dictPage(new DictPage)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QLineEdit *m_queryEdit = new QLineEdit;

    m_queryEdit->setFixedHeight(35);
    m_queryEdit->setPlaceholderText("输入您要翻译的单词或文字");
    m_queryEdit->setObjectName("QueryEdit");

    mainLayout->setContentsMargins(20, 10, 20, 0);
    mainLayout->addWidget(m_queryEdit);
    mainLayout->addSpacing(5);
    mainLayout->addLayout(m_layout);

    m_layout->addWidget(m_dailyPage);
    m_layout->addWidget(m_dictPage);

    connect(m_queryEdit, &QLineEdit::textChanged, this, [=] {
         if (m_queryEdit->text().isEmpty()) {
             m_layout->setCurrentIndex(0);
         } else {
             m_dictPage->queryWord(m_queryEdit->text());
             m_layout->setCurrentIndex(1);
         }
    });
}

HomePage::~HomePage()
{
}
