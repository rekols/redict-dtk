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

#include <QXmlStreamWriter>
#include <QXmlStreamReader>

#include <QDebug>
#include <QDateTime>

static YoudaoAPI *INSTANCE = nullptr;

YoudaoAPI* YoudaoAPI::instance()
{
    if (INSTANCE == nullptr) {
        INSTANCE = new YoudaoAPI;
    }

    return INSTANCE;
}

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
    QUrl url("http://dict.youdao.com/jsonresult");
    QUrlQuery query;
    query.addQueryItem("q", text);
    query.addQueryItem("type", "1");
    query.addQueryItem("client", "deskdict");
    query.addQueryItem("keyfrom", "deskdict_deepin");
    query.addQueryItem("pos", "-1");
    query.addQueryItem("len", "eng");
    url.setQuery(query.toString(QUrl::FullyEncoded));

    QNetworkRequest request(url);
    QNetworkReply *reply = m_http->get(request);

    connect(reply, &QNetworkReply::finished, this, &YoudaoAPI::handleQueryWordFinished);
}

void YoudaoAPI::suggest(const QString &text)
{
    QUrl url("http://dict.youdao.com/suggest");
    QUrlQuery query;
    query.addQueryItem("type", "DESKDICT");
    query.addQueryItem("client", "deskdict");
    query.addQueryItem("keyfrom", "deskdict_deepin");
    query.addQueryItem("num", "4");
    query.addQueryItem("q", text);
    query.addQueryItem("ver", "2.0");
    query.addQueryItem("le", "eng");
    query.addQueryItem("doctype", "json");
    url.setQuery(query.toString(QUrl::FullyEncoded));

    QNetworkRequest request(url);
    QNetworkReply *reply = m_http->get(request);

    connect(reply, &QNetworkReply::finished, this, &YoudaoAPI::handleSuggestFinished);
}

void YoudaoAPI::translate(const QString &text, const QString &type)
{
    QUrl url("http://fanyi.youdao.com/translate");
    QUrlQuery query;
    query.addQueryItem("dogVersion", "1.0");
    query.addQueryItem("ue", "utf8");
    query.addQueryItem("doctype", "json");
    query.addQueryItem("xmlVersion", "1.6");
    query.addQueryItem("client", "deskdict_deepin");
    query.addQueryItem("id", "92dc50aa4970fb72d");
    query.addQueryItem("vendor", "YoudaoDict");
    query.addQueryItem("appVer", "1.0.3");
    query.addQueryItem("appZengqiang", "0");
    query.addQueryItem("abTest", "5");
    query.addQueryItem("smartresult", "dict");
    query.addQueryItem("smartresult", "rule");
    query.addQueryItem("keyfrom", "deskdict.main");
    query.addQueryItem("i", text);
    query.addQueryItem("type", type);
    url.setQuery(query.toString(QUrl::FullyEncoded));

    QNetworkRequest request(url);
    QNetworkReply *reply = m_http->get(request);

    connect(reply, &QNetworkReply::finished, this, &YoudaoAPI::handleTranslateFinished);
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
    QNetworkReply *reply = m_http->get(request);

    connect(reply, &QNetworkReply::finished, this, &YoudaoAPI::handleQueryDailyFinished);
}

void YoudaoAPI::handleQueryWordFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());

    if (reply->error() != QNetworkReply::NoError) {
        return;
    }

    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    QJsonObject object = document.object();

    if (!document.isEmpty()) {
        QString queryWord = object.value("rq").toString();
        QString ukPhonetic = object.value("uksm").toString();
        QString usPhonetic = object.value("ussm").toString();
        QString basicExplains("");
        QString webReferences("");

        QJsonArray explain = object.value("basic").toArray();

        // get the basic data.
        for (const QJsonValue &value : explain) {
            basicExplains.append(value.toString());
            basicExplains.append("<br>");
        }

        // Access to the web references.
        QJsonArray webRefArray = object.value("web").toArray();
        if (!webRefArray.isEmpty()) {
            for (const QJsonValue &value : webRefArray) {
                QJsonObject obj = value.toObject();
                QString key = obj.keys().first();
                QJsonArray arr = obj.value(key).toArray();

                for (const QJsonValue &value : arr) {
                    webReferences += "<br>";
                    webReferences += QString("• %1 : %2").arg(key).arg(value.toString());
                    webReferences += "</br>";
                }
            }
        }

        emit searchFinished(std::make_tuple(queryWord, ukPhonetic, usPhonetic, basicExplains, webReferences));
    }
}

void YoudaoAPI::handleQueryDailyFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());

    if (reply->error() != QNetworkReply::NoError) {
        return;
    }

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

void YoudaoAPI::handleTranslateFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());

    if (reply->error() != QNetworkReply::NoError) {
        return;
    }

    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    QJsonArray array = document.object().value("translateResult").toArray();
    QString text;

    for (const QJsonValue &value : array) {
        QJsonArray arr = value.toArray();
        for (const QJsonValue &value : arr) {
            QString ret = value.toObject().value("tgt").toString();
            text += ret;
            text += "\n";
        }
    }

    emit translateFinished(text);
}

void YoudaoAPI::handleSuggestFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());

    if (reply->error() != QNetworkReply::NoError) {
        return;
    }

    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    QJsonObject object = document.object().value("data").toObject();
    QJsonArray array = object.value("entries").toArray();
    QStringList list;

    for (const QJsonValue &value : array) {
        QJsonObject obj = value.toObject();
        QString entry = obj.value("entry").toString();
        const QString explain = obj.value("explain").toString();

        entry.push_back(" | ");
        entry.push_back(explain);

        list << entry;
    }

    emit suggestFinished(list);
}
