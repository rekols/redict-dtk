#ifndef YOUDAOAPI_H
#define YOUDAOAPI_H

#include <QObject>

class QNetworkAccessManager;
class QNetworkRequest;
class QNetworkReply;

class YoudaoAPI : public QObject
{
    Q_OBJECT

public:
    YoudaoAPI(QObject *parent = 0);

    void searchWord(const QString &word);

private:
    QNetworkAccessManager *http;

private slots:
    void searchWordFinished(QNetworkReply *reply);

signals:
    void sendData(QString, QString, QString, QString);
};

#endif // YOUDAOAPI_H
