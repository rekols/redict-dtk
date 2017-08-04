#ifndef DATAPAGE_H
#define DATAPAGE_H

#include <QWidget>
#include <QVBoxLayout>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
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
    QHBoxLayout *imageLayout;
    QHBoxLayout *infoLayout;
    QLabel *imageLabel;
    QLabel *infoLabel;

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

signals:
    void loadImageFinished();
};

#endif // DATAPAGE_H
