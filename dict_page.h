#ifndef DICTPAGE_H
#define DICTPAGE_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkCookie>
#include <QNetworkCookieJar>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <dimagebutton.h>
#include <QMediaPlayer>

#include <QLineEdit>
#include <QPushButton>
#include <ddialog.h>

DWIDGET_USE_NAMESPACE

class DictPage : public QWidget
{
    Q_OBJECT

public:
    DictPage(QWidget *parent = 0);

    void queryWord(const QString &word);

    QNetworkAccessManager *http;

    DDialog *dialog;

    QVBoxLayout *layout;
    QHBoxLayout *searchLayout;
    QHBoxLayout *wordLayout;
    QHBoxLayout *pronLayout;
    QHBoxLayout *infoLayout;
    QHBoxLayout *youdaoLayout;

    QLineEdit *searchEdit;
    QPushButton *searchButton;
    QLabel *nameLabel;
    QLabel *pronLabel1;
    QLabel *pronLabel2;
    QLabel *infoLabel;

    DImageButton *pronButton1;
    DImageButton *pronButton2;

    QMediaPlayer *audio1;
    QMediaPlayer *audio2;

private:
    void init();


private slots:
    void replyfinished(QNetworkReply *reply);
    void start();
};

#endif // DICTPAGE_H
