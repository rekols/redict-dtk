#include "dict_page.h"
#include <QByteArray>
#include <QDebug>

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
    ukPron = new QLabel("");
    usPron = new QLabel("");
    infoLabel = new QLabel("");

    nameLabel->setWordWrap(true);
    infoLabel->setWordWrap(true);

    nameLabel->setStyleSheet("font-size: 22px; color:#2CA7F8;");
    ukPron->setStyleSheet("font-size: 13px");
    usPron->setStyleSheet("font-size: 13px");
    infoLabel->setStyleSheet("font-size: 17px");


    wordLayout->addSpacing(30);
    wordLayout->addWidget(nameLabel);
    wordLayout->addSpacing(30);

    infoLayout->addSpacing(30);
    infoLayout->addWidget(infoLabel);
    infoLayout->addSpacing(30);

    pronLayout->addSpacing(30);
    pronLayout->addWidget(ukPron);
    pronLayout->addSpacing(20);
    pronLayout->addWidget(usPron);
    pronLayout->addStretch();

    layout->addSpacing(20);
    layout->addLayout(wordLayout);
    layout->addLayout(pronLayout);
    layout->addSpacing(10);
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

    youdaoLayout->addSpacing(30);
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

        QJsonArray array = data.value("explains").toArray();
        QString explains = NULL;

        for (int i=0; i<array.size(); ++i)
        {
            explains.append(array.at(i).toString());
            explains.append("\n");
        }

        nameLabel->setText(object.value("query").toString());
        infoLabel->setText(explains);

        if (data.value("us-phonetic").toString().isEmpty() && data.value("uk-phonetic").toString().isEmpty())
        {
            usPron->setText("");
            ukPron->setText("");
            ukPron->setVisible(false);
            usPron->setVisible(false);

            if (array.isEmpty()) //如果没有解释，那就翻译
            {
                for (int i=0; i<object.value("translation").toArray().size(); ++i)
                {
                    infoLabel->setText(object.value("translation").toArray().at(i).toString());
                    infoLabel->setText(infoLabel->text() + "\n");
                }
            }

            if (!data.value("phonetic").toString().isEmpty()) //显示中文拼音
            {
                nameLabel->setText(nameLabel->text() + " [" +data.value("phonetic").toString() + "]");
            }
        }
        else
        {
            ukPron->setVisible(true);
            usPron->setVisible(true);

            usPron->setText(QString("美 [%1]").arg(data.value("us-phonetic").toString()));
            ukPron->setText(QString("英 [%1]").arg(data.value("uk-phonetic").toString()));
        }


    }
}
