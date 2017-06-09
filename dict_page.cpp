#include "dict_page.h"

DictPage::DictPage(QWidget *parent)
    : QWidget(parent)
{
    http = new QNetworkAccessManager(this);
    layout = new QVBoxLayout(this);
    topLayout = new QHBoxLayout();
    wordLayout = new QHBoxLayout();
    pronLayout = new QHBoxLayout();
    infoLayout = new QHBoxLayout();
    nameLabel = new QLabel("");
    ukPron = new QLabel("");
    usPron = new QLabel("");
    infoLabel = new QLabel("");
    returnButton = new DLinkButton("返回主页");

    nameLabel->setStyleSheet("font-size: 25px; color:#2CA7F8;");
    ukPron->setStyleSheet("font-size: 12px");
    usPron->setStyleSheet("font-size: 12px");
    infoLabel->setStyleSheet("font-size: 18px");

    topLayout->addSpacing(5);
    topLayout->addWidget(returnButton, 0, Qt::AlignLeft);

    wordLayout->addSpacing(30);
    wordLayout->addWidget(nameLabel);

    infoLayout->addSpacing(27);
    infoLayout->addWidget(infoLabel);

    pronLayout->addSpacing(30);
    pronLayout->addWidget(ukPron);
    pronLayout->addSpacing(20);
    pronLayout->addWidget(usPron);
    pronLayout->addStretch();

    layout->addLayout(topLayout);
    layout->addSpacing(20);
    layout->addLayout(wordLayout);
    layout->addLayout(pronLayout);
    layout->addSpacing(10);
    layout->addLayout(infoLayout);
    layout->addStretch();

    connect(http, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyfinished(QNetworkReply *)));
}

void DictPage::queryWord(const QString &word)
{
    QNetworkRequest request;
    request.setUrl(QUrl("http://www.shanbay.com/api/v1/bdc/search/?word=" + word));
    http->get(request);
}

void DictPage::replyfinished(QNetworkReply *reply)
{
    QJsonDocument m_json;
    QJsonObject m_object, m_data, m_pron, m_audio;

    QByteArray wordInformation = reply->readAll();

    m_json = QJsonDocument::fromJson(wordInformation);

    if (!m_json.isNull())
    {
        m_object = m_json.object();
        m_data = m_object.value("data").toObject();
        m_pron = m_data.value("pronunciations").toObject();
        m_audio = m_data.value("audio_addresses").toObject();

        nameLabel->setText(m_data.value("content").toString());
        ukPron->setText(QString("英 [%1]").arg(m_pron.value("uk").toString()));
        usPron->setText(QString("美 [%1]").arg(m_pron.value("us").toString()));
        infoLabel->setText(m_data.value("definition").toString());
    }

    QString message = m_object.value("msg").toString();

    if (message != "SUCCESS")
    {
        nameLabel->setText(message);

        ukPron->setText("");
        usPron->setText("");
        infoLabel->setText("");

        return;
    }
}
