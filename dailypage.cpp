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

#include "dailypage.h"
#include <QScrollArea>
#include <QVBoxLayout>
#include <QTimer>

DailyPage::DailyPage(QWidget *parent)
    : QWidget(parent),
      m_networkManager(new QNetworkAccessManager(this)),
      m_imageLabel(new QLabel),
      m_titleLabel(new QLabel),
      m_summaryLabel(new QLabel),
      m_timeLabel(new QLabel),
      m_api(new YoudaoAPI)
{
    QScrollArea *scrollArea = new QScrollArea;
    QWidget *contentWidget = new QWidget;
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setFocusPolicy(Qt::NoFocus);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(contentWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QVBoxLayout *contentLayout = new QVBoxLayout(contentWidget);

    m_imageLabel->setFixedHeight(200);
    m_imageLabel->setFixedWidth(530);
    m_imageLabel->setScaledContents(true);

    m_titleLabel->setWordWrap(true);
    m_summaryLabel->setWordWrap(true);
    m_timeLabel->setWordWrap(true);

    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(scrollArea);

    contentLayout->setContentsMargins(0, 0, 0, 0);
    contentLayout->addWidget(m_imageLabel);
    contentLayout->addSpacing(8);
    contentLayout->addWidget(m_titleLabel);
    contentLayout->addWidget(m_summaryLabel);
    contentLayout->addSpacing(10);
    contentLayout->addWidget(m_timeLabel);
    contentLayout->addStretch();

    QTimer::singleShot(100, m_api, &YoudaoAPI::queryDaily);

    connect(m_api, &YoudaoAPI::dailyFinished, this, &DailyPage::handleQueryFinished);
}

DailyPage::~DailyPage()
{
}

void DailyPage::handleQueryFinished(std::tuple<QString, QString, QString, QString, QString> data)
{
    m_titleLabel->setText(std::get<0>(data));
    m_summaryLabel->setText(std::get<1>(data));
    m_timeLabel->setText(std::get<2>(data));

    QNetworkRequest request(QUrl(std::get<4>(data)));
    m_networkManager->get(request);

    connect(m_networkManager, &QNetworkAccessManager::finished, this, [=] (QNetworkReply *reply) {
        QByteArray imgData = reply->readAll();
        if (!imgData.isEmpty()) {
            QPixmap pixmap;
            pixmap.loadFromData(imgData);
            m_imageLabel->setPixmap(pixmap);
        }

        emit loadFinished();
    });
}
