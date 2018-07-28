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
    void translate(const QString &text, const QString &type);
    void queryDaily();

signals:
    // 0. query word
    // 1. UK phonetic
    // 2. US phonetic
    // 3. basic explains
    // 4. web references
    void searchFinished(std::tuple<QString, QString, QString, QString, QString>);

    // 0. title
    // 1. summary
    // 2. time
    // 3. voice url
    // 4. image url
    void dailyFinished(std::tuple<QString, QString, QString, QString, QString>);

    void translateFinished(const QString result);

private slots:
    void handleQueryWordFinished();
    void handleQueryDailyFinished();
    void handleTranslateFinished();

private:
    QNetworkAccessManager *m_http;

};

#endif
