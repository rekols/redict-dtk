#include "youdao_api.h"
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

YoudaoAPI::YoudaoAPI(QObject *parent)
    : QObject(parent)
{
    http = new QNetworkAccessManager(this);
}

YoudaoAPI::~YoudaoAPI()
{
    delete http;
}

void YoudaoAPI::translation(const QString &text)
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
    http->get(request);

    connect(http, SIGNAL(finished(QNetworkReply*)), this, SLOT(getNetworkReplyFinished(QNetworkReply*)));
}

void YoudaoAPI::getNetworkReplyFinished(QNetworkReply *reply)
{
    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    QJsonObject object = document.object();
    QJsonObject data = object.value("basic").toObject();

    if (!document.isEmpty())
    {
        QString ukPhonetic = data.value("uk-phonetic").toString();
        QString usPhonetic = data.value("us-phonetic").toString();
        QString text = nullptr;

        QJsonArray explain = data.value("explains").toArray();

        if (explain.isEmpty()) {
            for (int i = 0; i < object.value("translation").toArray().size(); ++i) {
                text.append(object.value("translation").toArray().at(i).toString());
                text.append("\n");
            }
        }else {
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
