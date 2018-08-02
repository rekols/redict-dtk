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
#include "scrollarea.h"
#include <QVBoxLayout>
#include <QTimer>
#include <QFile>
#include <QDir>

DailyPage::DailyPage(QWidget *parent)
    : QWidget(parent),
      m_networkManager(new QNetworkAccessManager(this)),
      m_imageLabel(new QLabel),
      m_contentLabel(new QLabel),
      m_api(YoudaoAPI::instance())
{
    ScrollArea *scrollArea = new ScrollArea;
    QWidget *contentWidget = new QWidget;
    scrollArea->setWidget(contentWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QVBoxLayout *contentLayout = new QVBoxLayout(contentWidget);
    QVBoxLayout *textLayout = new QVBoxLayout;

    m_imageLabel->setFixedHeight(200);
    m_imageLabel->setFixedWidth(546);
    m_imageLabel->setScaledContents(true);

    m_contentLabel->setStyleSheet("QLabel { font-size: 15px; }");
    m_contentLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
    m_contentLabel->setWordWrap(true);

    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(scrollArea);

    textLayout->setContentsMargins(10, 0, 10, 0);
    textLayout->addSpacing(8);
    textLayout->addWidget(m_contentLabel);
    textLayout->addSpacing(10);

    contentLayout->setContentsMargins(0, 0, 0, 0);
    contentLayout->addWidget(m_imageLabel);
    contentLayout->addLayout(textLayout);
    contentLayout->addStretch();

    QTimer::singleShot(100, m_api, &YoudaoAPI::queryDaily);

    connect(m_api, &YoudaoAPI::dailyFinished, this, &DailyPage::handleQueryFinished);
}

DailyPage::~DailyPage()
{
}

void DailyPage::checkDirectory()
{
    const QString path = QString("%1/.local/share/redict").arg(QDir::homePath());

    if (!QDir(path).exists()) {
        QDir dir(path);
        dir.mkpath(".");
    }
}

void DailyPage::clearImageCache()
{
    QDir dir(QString("%1/.local/share/redict").arg(QDir::homePath()));
    QFileInfoList fileList = dir.entryInfoList(QDir::Files);

    for (const QFileInfo &file : fileList) {
        QFile f(file.filePath());
        f.remove();
        f.close();
    }
}

void DailyPage::handleQueryFinished(std::tuple<QString, QString, QString, QString, QString> data)
{
    QString dailyText;
    dailyText += QString("<p>%1</p>").arg(std::get<0>(data));
    dailyText += QString("<p>%1</p>").arg(std::get<1>(data));
    dailyText += QString("<p>%1</p>").arg(std::get<2>(data));

    m_contentLabel->setText(dailyText);
    checkDirectory();

    const QString picturePath = QString("%1/.local/share/redict/%2.jpeg").arg(QDir::homePath()).arg(std::get<2>(data));

    if (!QFile::exists(picturePath)) {
        // auto clear image cache.
        clearImageCache();

        QNetworkRequest request(QUrl(std::get<4>(data)));
        m_networkManager->get(request);

        connect(m_networkManager, &QNetworkAccessManager::finished, this,
                [=] (QNetworkReply *reply) {
                    QByteArray imgData = reply->readAll();

                    loadImage(imgData);

                    // save image file to local.
                    QFile file(picturePath);
                    if (file.open(QIODevice::Append)) {
                        file.write(imgData);
                    }
                    file.close();

                    m_networkManager->deleteLater();
                });
    } else {
        // open local file.
        QFile file(picturePath);
        if (file.open(QIODevice::ReadOnly)) {
            QByteArray imgData = file.readAll();
            loadImage(imgData);
        }
        file.close();
    }

}

void DailyPage::loadImage(const QByteArray &data)
{
    QPixmap pixmap;
    pixmap.loadFromData(data);
    m_imageLabel->setPixmap(pixmap);

    emit loadFinished();
}
