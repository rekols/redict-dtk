#include "translator_page.h"
#include <QLabel>
#include <QPushButton>

TranslatorPage::TranslatorPage(QWidget *parent)
    :QWidget(parent)
{
    layout = new QVBoxLayout;
    hLayout = new QHBoxLayout;
    original = new QPlainTextEdit;
    translator = new QPlainTextEdit;
    http = new QNetworkAccessManager(this);

    QLabel *tips1 = new QLabel("原文");
    QLabel *tips2 = new QLabel("译文");

    QPushButton *trBtn = new QPushButton("翻译");
    hLayout->addWidget(trBtn);

    translator->setReadOnly(true);

    layout->addWidget(tips1);
    layout->addWidget(original);
    layout->addSpacing(10);
    layout->addLayout(hLayout);
    layout->addSpacing(10);
    layout->addWidget(tips2);
    layout->addWidget(translator);

    setLayout(layout);

    this->setStyleSheet("QPlainTextEdit { border: 1px solid #505050;}");

    connect(http, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyfinished(QNetworkReply *)));
    connect(trBtn, SIGNAL(clicked()), this, SLOT(on_translator_clicked()));
}

void TranslatorPage::on_translator_clicked()
{
    QNetworkRequest request;
    request.setUrl(QUrl("http://fanyi.youdao.com/openapi.do?keyfrom=YouDaoCV&key=659600698&type=data&doctype=json&version=1.1&q=" + original->toPlainText()));
    http->get(request);
}

void TranslatorPage::replyfinished(QNetworkReply *reply)
{
    QJsonDocument json;
    QJsonObject object;

    QByteArray wordInformation = reply->readAll();

    json = QJsonDocument::fromJson(wordInformation);

    if (!json.isNull())
    {
        object = json.object();

        QString text;

        for (int i=0; i<object.value("translation").toArray().size(); ++i) {
            text.append(object.value("translation").toArray().at(i).toString());
            text.append("\n");
        }

        translator->setPlainText(text);
    }
}
