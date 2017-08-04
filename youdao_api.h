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

    void queryWord(const QString &word);

private:
    QNetworkAccessManager *http;

private slots:
    void queryWordFinished(QNetworkReply *reply);

signals:
    void searchWordFinished(QString, QString, QString, QString);
};

#endif // YOUDAOAPI_H
