#include "home_page.h"

HomePage::HomePage(QWidget *parent)
    : QWidget(parent)
{
    layout = new QVBoxLayout(this);
    topLayout = new QHBoxLayout();
    rightLayout = new QVBoxLayout();
    imageLabel = new QLabel();
    contentLabel = new QLabel();
    noteLabel = new QLabel();
    timeLabel = new QLabel();

    tips = new QLabel("加载中...");
    tips->setStyleSheet("font-size: 20px; color:#2CA7F8;");

    contentLabel->setStyleSheet("font-size: 14px;");
    noteLabel->setStyleSheet("font-size: 14px;");
    timeLabel->setStyleSheet("font-size: 12px;");

    http = new QNetworkAccessManager(this);
    http2 = new QNetworkAccessManager(this);

    rightLayout->addWidget(contentLabel);
    rightLayout->addWidget(noteLabel);
    rightLayout->addWidget(timeLabel);

    //topLayout->addStretch();
    topLayout->addWidget(imageLabel);
    topLayout->addSpacing(20);
    topLayout->addLayout(rightLayout);
    //topLayout->addStretch();

    layout->addSpacing(40);
    layout->addWidget(tips);
    layout->addSpacing(25);
    layout->addLayout(topLayout);
    layout->addStretch();

    layout->setMargin(25);

    connect(http, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyfinished(QNetworkReply *)));
    connect(http2, SIGNAL(finished(QNetworkReply *)), this, SLOT(loadImagefinished(QNetworkReply *)));

    QNetworkRequest request;
    request.setUrl(QUrl("http://open.iciba.com/dsapi/"));
    http->get(request);

    imageLabel->setFixedWidth(250);
    imageLabel->setFixedHeight(180);
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

    tips->setText("每日一句");
}
