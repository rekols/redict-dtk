#include "home_page.h"

HomePage::HomePage(QWidget *parent)
    : QWidget(parent)
{
    layout = new QVBoxLayout(this);
    imageLayout = new QHBoxLayout;
    infoLayout = new QHBoxLayout;
    imageLabel = new QLabel();
    infoLabel = new QLabel();

    http = new QNetworkAccessManager(this);
    http2 = new QNetworkAccessManager(this);

    imageLayout->addSpacing(15);
    imageLayout->addWidget(imageLabel);
    imageLayout->addSpacing(15);

    infoLayout->addSpacing(15);
    infoLayout->addWidget(infoLabel);
    infoLayout->addSpacing(15);

    layout->addSpacing(10);
    layout->addLayout(imageLayout);
    layout->addSpacing(10);
    layout->addLayout(infoLayout);

    imageLabel->setFixedHeight(200);
    imageLabel->setScaledContents(true);

    infoLabel->setStyleSheet("font-size: 14px;");
    infoLabel->setWordWrap(true);

    QNetworkRequest request;
    request.setUrl(QUrl("http://open.iciba.com/dsapi/"));
    http->get(request);

    connect(http, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyfinished(QNetworkReply *)));
    connect(http2, SIGNAL(finished(QNetworkReply *)), this, SLOT(loadImagefinished(QNetworkReply *)));
}

HomePage::~HomePage()
{
    delete http;
    delete http2;
}

void HomePage::replyfinished(QNetworkReply *reply)
{
    QByteArray wordInformation = reply->readAll();

    QJsonDocument m_doc = QJsonDocument::fromJson(wordInformation);

    QJsonObject m_object;

    if (!m_doc.isNull())
    {
        m_object = m_doc.object();
        m_content = m_object.value("content").toString();
        m_note = m_object.value("note").toString();
        m_dateline = m_object.value("dateline").toString();
        m_picture = m_object.value("picture").toString();
    }

    if (!m_picture.isEmpty())
    {
        QNetworkRequest request;
        request.setUrl(QUrl(m_picture));
        http2->get(request);
    }

    QString info = NULL;
    info.append(m_content);
    info.append("\n");
    info.append(m_note);
    info.append("\n\n");
    info.append(m_dateline);

    infoLabel->setText(info);
}

void HomePage::loadImagefinished(QNetworkReply *reply)
{
    QByteArray data = reply->readAll();
    QPixmap pixmap;
    pixmap.loadFromData(data);
    imageLabel->setPixmap(pixmap);
}
