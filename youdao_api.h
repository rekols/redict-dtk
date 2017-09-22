#ifndef YOUDAO_API_H
#define YOUDAO_API_H

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

    void translation(const QString &text);

private:
    QNetworkAccessManager *http;

private slots:
    void getNetworkReplyFinished(QNetworkReply *);

signals:
    void finished(QString, QString, QString, QString);
};

#endif // YOUDAO_API_H
