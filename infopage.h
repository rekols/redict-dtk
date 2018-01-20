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

#ifndef INFOPAGE_H
#define INFOPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QLabel>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

class InfoPage : public QWidget
{
    Q_OBJECT

public:
    InfoPage(QWidget *parent = nullptr);
    ~InfoPage();
    
private:
    void loadData();
    void loadPicture(const QString &imgUrl);
    void handleData();
    void handlePictureData();

private:
    QNetworkAccessManager *m_http;
    QWidget *m_contentFrame;
    QVBoxLayout *m_contentLayout;
    QScrollArea *m_contentArea;
    QLabel *m_pictureLabel;
    QLabel *m_enLabel;
    QLabel *m_zhLabel;
    QLabel *m_dateLabel;
};

#endif
