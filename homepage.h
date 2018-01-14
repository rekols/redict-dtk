#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include <QLabel>
#include <QStackedLayout>
#include "dictpage.h"

class HomePage : public QWidget
{
    Q_OBJECT

public:
    explicit HomePage(QWidget *parent = nullptr);
    ~HomePage();

    void queryWord(const QString &text);

private:
    void loadBasicData();
    void loadPicture(const QString &imgUrl);
    void handleBasicData();
    void handlePictureData();

private:
    QNetworkAccessManager *m_http;
    QStackedLayout *m_mainLayout;
    DictPage *m_dictPage;
    QLabel *m_pictureLabel;
    QLabel *m_enLabel;
    QLabel *m_zhLabel;
    QLabel *m_dateLabel;
};

#endif // HOMEPAGE_H
