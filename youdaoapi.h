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

#ifndef YOUDAOAPI_H
#define YOUDAOAPI_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

class YoudaoAPI : public QObject
{
    Q_OBJECT

public:
    YoudaoAPI(QObject *parent = nullptr);
    ~YoudaoAPI();

    void queryWord(const QString &text);

signals:
    void finished(const QString &queryText, const QString &ukPhonetic,
                  const QString &usPhonetic, const QString &translationText);

private slots:
    void replyFinished(QNetworkReply *);

private:
    QNetworkAccessManager *m_http;

};

#endif
