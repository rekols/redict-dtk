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

#include "youdaoapi.h"
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QDebug>
#include <QDateTime>

YoudaoAPI::YoudaoAPI(QObject *parent)
    : QObject(parent),
      m_http(new QNetworkAccessManager(this))
{
}

YoudaoAPI::~YoudaoAPI()
{
    delete m_http;
}

void YoudaoAPI::queryWord(const QString &text)
{
    QUrl url("http://fanyi.youdao.com/openapi.do");
    QUrlQuery query;
    query.addQueryItem("keyfrom", "YouDaoCV");
    query.addQueryItem("key", "659600698");
    query.addQueryItem("type", "data");
    query.addQueryItem("doctype", "json");
    query.addQueryItem("version", "1.1");
    query.addQueryItem("q", text);
    url.setQuery(query.toString(QUrl::FullyEncoded));

    QNetworkRequest request(url);
    m_http->get(request);

    connect(m_http, &QNetworkAccessManager::finished, this, &YoudaoAPI::queryWordFinished);
}

void YoudaoAPI::queryDaily()
{
    QUrl url("http://dict.youdao.com/infoline/style/cardList");
    QUrlQuery query;
    query.addQueryItem("apiversion", "3.0");
    query.addQueryItem("client", "deskdict");
    query.addQueryItem("style", "daily");
    query.addQueryItem("lastId", "0");
    query.addQueryItem("keyfrom", "deskdict.8.1.2.0");
    query.addQueryItem("size", "1");
    url.setQuery(query.toString(QUrl::FullyEncoded));

    QNetworkRequest request(url);
    m_http->get(request);

    connect(m_http, &QNetworkAccessManager::finished, this, &YoudaoAPI::queryDailyFinished);
}

void YoudaoAPI::queryWordFinished(QNetworkReply *reply)
{
    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    QJsonObject object = document.object();
    QJsonObject dataObj = object.value("basic").toObject();

    if (!document.isEmpty()) {
        QString queryWord = object.value("query").toString();
        QString ukPhonetic = dataObj.value("uk-phonetic").toString();
        QString usPhonetic = dataObj.value("us-phonetic").toString();
        QString basicExplains("");
        QString webReferences("");

        QJsonArray explain = dataObj.value("explains").toArray();

        // get the basic data.
        if (explain.isEmpty()) {
            for (int i = 0; i < object.value("translation").toArray().size(); ++i) {
                basicExplains.append(object.value("translation").toArray().at(i).toString());
                basicExplains.append("\n");
            }
        } else {
            for (int i = 0; i < explain.size(); ++i) {
                basicExplains.append(explain.at(i).toString());
                basicExplains.append("\n");
            }
        }

        // Access to the web references.
        QJsonArray webRefArray = object.value("web").toArray();
        if (!webRefArray.isEmpty()) {
            for (int i = 0; i < webRefArray.size(); ++i) {
                QJsonObject obj = webRefArray.at(i).toObject();

                // QJsonArray valueArray = obj.value("value").toArray();
                // for (int i = 0; i < valueArray.size(); ++i) {
                //     webReferences += valueArray.at(i).toString() + " ";
                // }

                webReferences += QString("• %1 :   ").arg(obj.value("key").toString());
                webReferences += obj.value("value").toArray().at(0).toString();
                webReferences += "\n";
            }
        }

        emit searchFinished(std::make_tuple(queryWord, ukPhonetic, usPhonetic, basicExplains, webReferences));
    }

}

void YoudaoAPI::queryDailyFinished(QNetworkReply *reply)
{
    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    QJsonObject object = document.array().at(0).toObject();

    const QString title = object.value("title").toString();
    const QString summary = object.value("summary").toString();
    const QString voiceURL = object.value("voice").toString();
    const QString imageURL = object.value("gif").toArray().at(0).toString();
    const long long startTime = object.value("startTime").toVariant().toLongLong();

    QDateTime dateTime;
    QString time;

    dateTime = QDateTime::fromString(QString::number(startTime), "yyyyMMddhhmm");
    time = dateTime.toString("yyyy-MM-dd");

    emit dailyFinished(std::make_tuple(title, summary, time, voiceURL, imageURL));
}
