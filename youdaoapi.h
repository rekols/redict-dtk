#ifndef YOUDAOAPI_H
#define YOUDAOAPI_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

class YoudaoAPI : public QObject
{
    Q_OBJECT

public:
    YoudaoAPI(QObject *parent = nullptr);
    ~YoudaoAPI();

    void queryWord(const QString &text);

private:
    QNetworkAccessManager *http;

private slots:
    void getNetworkReplyFinished(QNetworkReply *);

signals:
    void finished(QString, QString, QString, QString);
};

#endif // YOUDAOAPI_H
