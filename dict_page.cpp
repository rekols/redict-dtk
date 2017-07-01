#include "dict_page.h"
#include <QByteArray>

DictPage::DictPage(QWidget *parent)
    : QWidget(parent)
{
    http = new QNetworkAccessManager(this);
    layout = new QVBoxLayout(this);
    topLayout = new QHBoxLayout();
    wordLayout = new QHBoxLayout();
    pronLayout = new QHBoxLayout();
    infoLayout = new QHBoxLayout();
    youdaoLayout = new QHBoxLayout();
    nameLabel = new QLabel("加载中...");
    ukPron = new QLabel("");
    usPron = new QLabel("");
    infoLabel = new QLabel("");
    returnButton = new DLinkButton("返回主页");

    infoLabel->setWordWrap(true);

    nameLabel->setStyleSheet("font-size: 22px; color:#2CA7F8;");
    ukPron->setStyleSheet("font-size: 13px");
    usPron->setStyleSheet("font-size: 13px");
    infoLabel->setStyleSheet("font-size: 17px");

    topLayout->addSpacing(5);
    topLayout->addWidget(returnButton, 0, Qt::AlignLeft);

    wordLayout->addSpacing(30);
    wordLayout->addWidget(nameLabel);

    infoLayout->addSpacing(30);
    infoLayout->addWidget(infoLabel);
    infoLayout->addSpacing(30);

    pronLayout->addSpacing(30);
    pronLayout->addWidget(ukPron);
    pronLayout->addSpacing(20);
    pronLayout->addWidget(usPron);
    pronLayout->addStretch();

    layout->addLayout(topLayout);
    layout->addSpacing(30);
    layout->addLayout(wordLayout);
    layout->addLayout(pronLayout);
    layout->addSpacing(10);
    layout->addLayout(infoLayout);
    layout->addSpacing(20);
    layout->addLayout(youdaoLayout);
    layout->addStretch();

    connect(http, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyfinished(QNetworkReply *)));

    init();
}

void DictPage::init()
{
    QPixmap iconPixmap = QPixmap(":/image/youdao-dict.svg");
    QLabel *iconLabel = new QLabel;
    iconLabel->setFixedSize(24, 24);
    iconLabel->setScaledContents(true);
    iconLabel->setPixmap(iconPixmap);

    QLabel *tips = new QLabel("数据来自有道词典");

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
    QJsonDocument m_json;
    QJsonObject m_object, m_data;

    QByteArray wordInformation = reply->readAll();

    m_json = QJsonDocument::fromJson(wordInformation);

    if (!m_json.isNull())
    {
        m_object = m_json.object();
        m_data = m_object.value("basic").toObject();

        QJsonArray array = m_data.value("explains").toArray();
        QString explains = NULL;

        for (int i=0; i<array.size(); ++i)
        {
            explains.append(array.at(i).toString());
            explains.append("\n");
        }

        nameLabel->setText(m_object.value("query").toString());
        infoLabel->setText(explains);

        if (m_data.value("us-phonetic").toString().isEmpty() && m_data.value("uk-phonetic").toString().isEmpty())
        {
            usPron->setText("");
            ukPron->setText("");
        
            for (int i=0; i<m_object.value("translation").toArray().size(); ++i)
            {
                infoLabel->setText(m_object.value("translation").toArray().at(i).toString());
                infoLabel->setText(infoLabel->text() + "\n");
            }
        }
        else
        {
            usPron->setText(QString("美 [%1]").arg(m_data.value("us-phonetic").toString()));
            ukPron->setText(QString("英 [%1]").arg(m_data.value("uk-phonetic").toString()));
        }

    }
}
