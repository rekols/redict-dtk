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
#include <QPushButton>
#include <QTimer>

HomePage::HomePage(QWidget *parent)
    : QWidget(parent),
      m_layout(new QStackedLayout),
      m_dailyPage(new DailyPage),
      m_dictPage(new DictPage),
      m_loadPage(new LoadPage),
      m_queryEdit(new QueryEdit)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QPushButton *queryBtn = new QPushButton("查询");

    QHBoxLayout *queryLayout = new QHBoxLayout;
    queryLayout->addWidget(m_queryEdit);
    queryLayout->addWidget(queryBtn);
    queryLayout->setSpacing(0);
    queryLayout->setMargin(0);

    queryBtn->setFocusPolicy(Qt::NoFocus);
    queryBtn->setObjectName("QueryBtn");
    queryBtn->setFixedSize(90, 35);

    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->addLayout(queryLayout);
    mainLayout->addLayout(m_layout);

    m_layout->setMargin(0);
    m_layout->setSpacing(0);
    m_layout->addWidget(m_dailyPage);
    m_layout->addWidget(m_dictPage);
    m_layout->addWidget(m_loadPage);

    setFocusPolicy(Qt::ClickFocus);

    m_layout->setCurrentIndex(2);
    m_loadPage->start();

    connect(m_queryEdit, &QLineEdit::returnPressed, this, &HomePage::queryWord);
    connect(m_queryEdit, &QLineEdit::textChanged, this, &HomePage::queryWord);
    connect(queryBtn, &QPushButton::clicked, this, &HomePage::queryWord);

    connect(m_dailyPage, &DailyPage::loadFinished, this,
            [=] {
                m_layout->setCurrentIndex(0);
                m_loadPage->stop();
            });
}

HomePage::~HomePage()
{
}

void HomePage::queryWord()
{
    const QString &text = m_queryEdit->text();

    if (text.isEmpty()) {
        m_layout->setCurrentIndex(0);
    } else {
        m_layout->setCurrentIndex(1);
        m_dictPage->queryWord(m_queryEdit->text());
    }
}
