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

#include "popupcontent.h"
#include <QScrollArea>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QLabel>

PopupContent::PopupContent(QWidget *parent)
    : DAbstractDialog(parent),
      m_queryLabel(new QLabel),
      m_transLabel(new QLabel)
{
    DBlurEffectWidget *bgWidget = new DBlurEffectWidget(this);
    bgWidget->setBlendMode(DBlurEffectWidget::BehindWindowBlend);
    bgWidget->setMaskColor(DBlurEffectWidget::LightColor);

    QScrollArea *contentFrame = new QScrollArea;
    contentFrame->setWidgetResizable(true);
    contentFrame->setStyleSheet(contentFrame->styleSheet()
                                + "QScrollArea { background: transparent; }" 
                                + "QScrollArea > QWidget > QWidget { background: transparent; }");

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(contentFrame);
    layout->setMargin(0);

    QWidget *mainWidget = new QWidget;
    QVBoxLayout *mainLayout = new QVBoxLayout(mainWidget);
    contentFrame->setWidget(mainWidget);

    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->addWidget(m_queryLabel);
    mainLayout->addWidget(m_transLabel);
    mainLayout->addStretch();

    m_queryLabel->setWordWrap(true);
    m_transLabel->setWordWrap(true);

    setFixedSize(300, 200);
    bgWidget->resize(size());
}

PopupContent::~PopupContent()
{
}

void PopupContent::mouseMoveEvent(QMouseEvent *e)
{
    // disable move window.
    e->ignore();
}

void PopupContent::updateContent(const QString &queryText, const QString &ukPhonetic,
                                 const QString &usPhonetic, const QString &translationText)
{
    m_queryLabel->setText(queryText);
    m_transLabel->setText(translationText);
}
