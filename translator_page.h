#ifndef TRANSLATORPAGE_H
#define TRANSLATORPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPlainTextEdit>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkCookie>
#include <QNetworkCookieJar>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include <QKeyEvent>

class TranslatorPage : public QWidget
{
    Q_OBJECT

public:
    TranslatorPage(QWidget *parent = 0);

    QVBoxLayout *layout;
    QHBoxLayout *hLayout;
    QPlainTextEdit *original;
    QPlainTextEdit *translator;

    QNetworkAccessManager *http;

protected:
    void keyPressEvent(QKeyEvent *);

private slots:
    void replyfinished(QNetworkReply *reply);
    void on_translator_clicked();
};

#endif // TRANSLATORPAGE_H
