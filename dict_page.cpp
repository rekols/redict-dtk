#include "dict_page.h"
#include <QByteArray>

DictPage::DictPage(QWidget *parent)
    : QWidget(parent)
{
    http = new QNetworkAccessManager(this);
    layout = new QVBoxLayout(this);
    wordLayout = new QHBoxLayout();
    pronLayout = new QHBoxLayout();
    infoLayout = new QHBoxLayout();
    youdaoLayout = new QHBoxLayout();
    nameLabel = new QLabel("加载中...");
    pronLabel = new QLabel("");
    infoLabel = new QLabel("");

    nameLabel->setWordWrap(true);
    infoLabel->setWordWrap(true);

    nameLabel->setStyleSheet("font-size: 22px; color:#2CA7F8;");
    pronLabel->setStyleSheet("font-size: 13px");
    infoLabel->setStyleSheet("font-size: 17px");

    wordLayout->addSpacing(35);
    wordLayout->addWidget(nameLabel);
    wordLayout->addSpacing(35);

    infoLayout->addSpacing(35);
    infoLayout->addWidget(infoLabel);
    infoLayout->addSpacing(35);

    pronLayout->addSpacing(35);
    pronLayout->addWidget(pronLabel);
    pronLayout->addSpacing(35);

    layout->addSpacing(20);
    layout->addLayout(wordLayout);
    layout->addLayout(pronLayout);
    layout->addSpacing(12);
    layout->addLayout(infoLayout);
    layout->addStretch();
    layout->addLayout(youdaoLayout);
    layout->addSpacing(20);

    connect(http, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyfinished(QNetworkReply *)));

    init();
}

void DictPage::init()
{
    QPixmap iconPixmap = QPixmap(":/image/youdao-dict.svg");
    QLabel *iconLabel = new QLabel;
    iconLabel->setFixedSize(20, 20);
    iconLabel->setScaledContents(true);
    iconLabel->setPixmap(iconPixmap);

    QLabel *tips = new QLabel("数据来自有道词典");
    tips->setStyleSheet("QLabel {font-size: 12px; }");

    youdaoLayout->addSpacing(35);
    youdaoLayout->addWidget(iconLabel);
    youdaoLayout->addWidget(tips);
}

void DictPage::queryWord(const QString &word)
{
    QNetworkRequest request;
    request.setUrl(QUrl("http://fanyi.youdao.com/openapi.do?keyfrom=YouDaoCV&key=659600698&type=data&doctype=json&version=1.1&q=" + word));
    http->get(request);
}

void DictPage::replyfinished(QNetworkReply *reply)
{
    QJsonDocument json;
    QJsonObject object, data;

    QByteArray wordInformation = reply->readAll();

    json = QJsonDocument::fromJson(wordInformation);

    if (!json.isNull())
    {
        object = json.object();
        data = object.value("basic").toObject();

        QString uk_phonetic = data.value("uk-phonetic").toString();
        QString us_phonetic = data.value("us-phonetic").toString();
        QString text = NULL;

        QJsonArray explain = data.value("explains").toArray();

        nameLabel->setText(object.value("query").toString());

        if (uk_phonetic.isEmpty() && us_phonetic.isEmpty()) {
            pronLabel->setVisible(false);
            if (!data.value("phonetic").toString().isEmpty()) {
                nameLabel->setText(nameLabel->text() + " [" + data.value("phonetic").toString() + "]");
            }
        }else {
            pronLabel->setVisible(true);
            pronLabel->setText(QString("英[%1]        美[%2]").arg(uk_phonetic).arg(us_phonetic));
        }

        if (explain.isEmpty()) {
            for (int i=0; i<object.value("translation").toArray().size(); ++i) {
                text.append(object.value("translation").toArray().at(i).toString());
                text.append("\n");
            }
        }else {
            for (int i=0; i<explain.size(); ++i) {
                text.append(explain.at(i).toString());
                text.append("\n");
            }
        }

        infoLabel->setText(text);
    }
}
