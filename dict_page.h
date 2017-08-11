#ifndef DICTPAGE_H
#define DICTPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <dimagebutton.h>
#include <QMediaPlayer>
#include <QLineEdit>
#include <QPushButton>
#include "youdao_api.h"

DWIDGET_USE_NAMESPACE

class DictPage : public QWidget
{
    Q_OBJECT

public:
    DictPage(QWidget *parent = 0);

    void queryWord(const QString &word);
    void changeTheme(const QString &theme);

    QVBoxLayout *layout;
    QHBoxLayout *wordLayout;
    QHBoxLayout *pronLayout;
    QHBoxLayout *infoLayout;
    QHBoxLayout *youdaoLayout;

    QLabel *nameLabel;
    QLabel *pronLabel1;
    QLabel *pronLabel2;
    QLabel *infoLabel;

    DImageButton *pronButton1;
    DImageButton *pronButton2;

    QMediaPlayer *audio;

    YoudaoAPI *api;

    void init();

private slots:
    void start();
    void processingData(QString, QString, QString, QString);
};

#endif // DICTPAGE_H
