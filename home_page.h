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
#include <QLineEdit>
#include <QPushButton>

class HomePage : public QWidget
{
    Q_OBJECT

public:
    HomePage(QWidget *parent = 0);
    ~HomePage();

private:
    QVBoxLayout *layout;
    QHBoxLayout *searchLayout;
    QHBoxLayout *topLayout;
    QVBoxLayout *rightLayout;
    QLineEdit *searchEdit;
    QPushButton *searchButton;
    QLabel *tips;
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

signals:
    void searchWord(QString word);


private slots:
    void searchEmit();
    void replyfinished(QNetworkReply *reply);
    void loadImagefinished(QNetworkReply *reply);
};

#endif // HOMEPAGE_H
