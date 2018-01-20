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

#include "infopage.h"
#include <QLabel>
#include <QDebug>

InfoPage::InfoPage(QWidget *parent)
    : QWidget(parent),
      m_http(new QNetworkAccessManager(this)),
      m_contentFrame(new QWidget),
      m_contentLayout(new QVBoxLayout(m_contentFrame)),
      m_contentArea(new QScrollArea),
      m_pictureLabel(new QLabel),
      m_enLabel(new QLabel),
      m_zhLabel(new QLabel),
      m_dateLabel(new QLabel)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setMargin(0);
    mainLayout->addWidget(m_contentArea);

    m_pictureLabel->setScaledContents(true);
    m_enLabel->setWordWrap(true);
    m_zhLabel->setWordWrap(true);
    m_dateLabel->setWordWrap(true);

    QVBoxLayout *textLayout = new QVBoxLayout;
    textLayout->addWidget(m_enLabel);
    textLayout->addWidget(m_zhLabel);
    textLayout->addWidget(m_dateLabel);
    textLayout->setSpacing(0);
    textLayout->setContentsMargins(10, 5, 10, 0);

    m_contentLayout->setMargin(0);
    m_contentLayout->addWidget(m_pictureLabel);
    m_contentLayout->addLayout(textLayout);

    m_contentArea->setContentsMargins(0, 0, 0, 0);
    m_contentArea->setWidgetResizable(true);
    m_contentArea->setWidget(m_contentFrame);

    loadData();
}

InfoPage::~InfoPage()
{
}

void InfoPage::loadData()
{
    QNetworkRequest request(QUrl("http://open.iciba.com/dsapi/"));
    QNetworkReply *reply = m_http->get(request);
    connect(reply, &QNetworkReply::finished, this, &InfoPage::handleData);
}

void InfoPage::loadPicture(const QString &imgUrl)
{
    QUrl url;
    url.setUrl(imgUrl);

    QNetworkRequest request(url);
    QNetworkReply *reply = m_http->get(request);
    connect(reply, &QNetworkReply::finished, this, &InfoPage::handlePictureData);
}

void InfoPage::handleData()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    QJsonDocument jsonDoc = QJsonDocument::fromJson(QByteArray(reply->readAll()));
    QJsonObject jsonObj = jsonDoc.object();
    QString enContent = jsonObj.value("content").toString();
    QString zhContent = jsonObj.value("note").toString();
    QString dateLine = jsonObj.value("dateline").toString();
    QString imgUrl = jsonObj.value("picture").toString();

    m_enLabel->setText(enContent);
    m_zhLabel->setText(zhContent);
    m_dateLabel->setText(dateLine);

    if (!imgUrl.isEmpty()) {
        loadPicture(imgUrl);
    }
}

void InfoPage::handlePictureData()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    const QByteArray data = reply->readAll();
    QPixmap pixmap;

    pixmap.loadFromData(data);
    m_pictureLabel->setPixmap(pixmap);

    m_enLabel->show();
    m_zhLabel->show();
    m_dateLabel->show();
}
