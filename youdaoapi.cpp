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

    connect(m_http, SIGNAL(finished(QNetworkReply *)), this, SLOT(queryWordFinished(QNetworkReply *)));
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

    connect(m_http, SIGNAL(finished(QNetworkReply *)), this, SLOT(queryDailyFinished(QNetworkReply *)));
}

void YoudaoAPI::queryWordFinished(QNetworkReply *reply)
{
    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    QJsonObject object = document.object();
    QJsonObject data = object.value("basic").toObject();

    if (!document.isEmpty()) {
        QString ukPhonetic = data.value("uk-phonetic").toString();
        QString usPhonetic = data.value("us-phonetic").toString();
        QString text = nullptr;

        QJsonArray explain = data.value("explains").toArray();

        if (explain.isEmpty()) {
            for (int i = 0; i < object.value("translation").toArray().size(); ++i) {
                text.append(object.value("translation").toArray().at(i).toString());
                text.append("\n");
            }
        } else {
            for (int i = 0; i < explain.size(); ++i) {
                text.append(explain.at(i).toString());
                text.append("\n");
            }
        }

        emit finished(object.value("query").toString(),
                      ukPhonetic,
                      usPhonetic,
                      text);
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

    emit dailyFinished(std::make_tuple(title, summary, voiceURL, imageURL));
}
