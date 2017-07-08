#include "home_page.h"

HomePage::HomePage(QWidget *parent)
    : QWidget(parent)
{
    layout = new QVBoxLayout(this);
    imageLabel = new QLabel();
    contentLabel = new QLabel();
    noteLabel = new QLabel();
    timeLabel = new QLabel();

    contentLabel->setStyleSheet("font-size: 14px;");
    noteLabel->setStyleSheet("font-size: 14px;");
    timeLabel->setStyleSheet("font-size: 12px;");

    http = new QNetworkAccessManager(this);
    http2 = new QNetworkAccessManager(this);

    layout->setMargin(20);
    layout->addStretch();
    layout->addWidget(imageLabel);
    layout->addSpacing(10);
    layout->addWidget(contentLabel);
    layout->addWidget(noteLabel);
    layout->addWidget(timeLabel);
    layout->addStretch();

    connect(http, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyfinished(QNetworkReply *)));
    connect(http2, SIGNAL(finished(QNetworkReply *)), this, SLOT(loadImagefinished(QNetworkReply *)));

    QNetworkRequest request;
    request.setUrl(QUrl("http://open.iciba.com/dsapi/"));
    http->get(request);

    imageLabel->setFixedHeight(200);
    imageLabel->setScaledContents(true);

    contentLabel->setWordWrap(true);
    contentLabel->setAlignment(Qt::AlignTop);

    noteLabel->setWordWrap(true);
    noteLabel->setAlignment(Qt::AlignTop);

    timeLabel->setWordWrap(true);
    timeLabel->setAlignment(Qt::AlignTop);
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

    contentLabel->setText(m_content);
    noteLabel->setText(m_note);
    timeLabel->setText(m_dateline);
}

void HomePage::loadImagefinished(QNetworkReply *reply)
{
    QByteArray data = reply->readAll();
    QPixmap pixmap;
    pixmap.loadFromData(data);
    imageLabel->setPixmap(pixmap);
}
