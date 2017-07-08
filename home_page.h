#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QVBoxLayout>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkCookie>
#include <QNetworkCookieJar>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include <QLabel>

class HomePage : public QWidget
{
    Q_OBJECT

public:
    HomePage(QWidget *parent = 0);
    ~HomePage();

private:
    QVBoxLayout *layout;
    QLabel *imageLabel;
    QLabel *contentLabel;
    QLabel *noteLabel;
    QLabel *timeLabel;

    QNetworkAccessManager *http;
    QNetworkAccessManager *http2;

    QString m_content;
    QString m_note;
    QString m_dateline;
    QString m_picture;

    void loadImage();

private slots:
    void replyfinished(QNetworkReply *reply);
    void loadImagefinished(QNetworkReply *reply);
};

#endif // HOMEPAGE_H
