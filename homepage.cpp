#include "homepage.h"

HomePage::HomePage(QWidget *parent)
    : QWidget(parent),
      m_http(new QNetworkAccessManager(this)),
      m_mainLayout(new QStackedLayout(this)),
      m_dictPage(new DictPage),
      m_pictureLabel(new QLabel),
      m_enLabel(new QLabel),
      m_zhLabel(new QLabel),
      m_dateLabel(new QLabel)
{
    QWidget *homeWidget = new QWidget;
    QVBoxLayout *homeLayout = new QVBoxLayout(homeWidget);
    QVBoxLayout *contentLayout = new QVBoxLayout;

    homeLayout->addWidget(m_pictureLabel);
    homeLayout->addSpacing(15);
    homeLayout->addLayout(contentLayout);
    homeLayout->addStretch();
    homeLayout->setSpacing(0);
    homeLayout->setContentsMargins(1, 0, 1, 0);

    contentLayout->addWidget(m_enLabel);
    contentLayout->addSpacing(5);
    contentLayout->addWidget(m_zhLabel);
    contentLayout->addSpacing(15);
    contentLayout->addWidget(m_dateLabel);
    contentLayout->setContentsMargins(15, 0, 15, 0);

    m_mainLayout->addWidget(homeWidget);
    m_mainLayout->addWidget(m_dictPage);

    m_enLabel->setWordWrap(true);
    m_zhLabel->setWordWrap(true);
    m_dateLabel->setWordWrap(true);

    m_enLabel->hide();
    m_zhLabel->hide();
    m_dateLabel->hide();

    m_pictureLabel->setScaledContents(true);
    m_pictureLabel->setFixedHeight(this->height() / 2);

    loadBasicData();
}

HomePage::~HomePage()
{
    delete m_http;
}

void HomePage::queryWord(const QString &text)
{
    if (text.isEmpty()) {
        m_mainLayout->setCurrentIndex(0);
        return;
    }

    m_dictPage->queryWord(text);
    m_mainLayout->setCurrentIndex(1);
}

void HomePage::loadBasicData()
{
    QNetworkRequest request(QUrl("http://open.iciba.com/dsapi/"));
    QNetworkReply *reply = m_http->get(request);
    connect(reply, &QNetworkReply::finished, this, &HomePage::handleBasicData);
}

void HomePage::loadPicture(const QString &imgUrl)
{
    QUrl url;
    url.setUrl(imgUrl);

    QNetworkRequest request(url);
    QNetworkReply *reply = m_http->get(request);
    connect(reply, &QNetworkReply::finished, this, &HomePage::handlePictureData);
}

void HomePage::handleBasicData()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    QJsonDocument jsonDoc = QJsonDocument::fromJson(QByteArray(reply->readAll()));
    QJsonObject jsonObj = jsonDoc.object();
    QString enContent = jsonObj.value("content").toString();
    QString zhContent = jsonObj.value("note").toString();
    QString dateLine = jsonObj.value("dateline").toString();
    QString imgUrl = jsonObj.value("picture").toString();

    m_enLabel->setText(enContent);
    m_zhLabel->setText(zhContent);
    m_dateLabel->setText(dateLine);

    if (!imgUrl.isEmpty()) {
        loadPicture(imgUrl);
    }
}

void HomePage::handlePictureData()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    const QByteArray data = reply->readAll();
    QPixmap pixmap;

    pixmap.loadFromData(data);
    m_pictureLabel->setPixmap(pixmap);

    m_enLabel->show();
    m_zhLabel->show();
    m_dateLabel->show();
}
