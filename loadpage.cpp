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

#include "loadpage.h"
#include <QVBoxLayout>

LoadPage::LoadPage(QWidget *parent)
    : QWidget(parent),
      m_spinner(new DSpinner),
      m_isFinished(false)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_spinner, 0, Qt::AlignHCenter);

    m_spinner->setFixedSize(30, 30);
    m_spinner->stop();
}

LoadPage::~LoadPage()
{
}

void LoadPage::start()
{
    m_spinner->start();
}

void LoadPage::stop()
{
    m_isFinished = true;
    m_spinner->stop();
}
