#ifndef DICTPAGE_H
#define DICTPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include "youdaoapi.h"
#include "dimagebutton.h"

DWIDGET_USE_NAMESPACE

class DictPage : public QWidget
{
    Q_OBJECT

public:
    DictPage(QWidget *parent = nullptr);
    ~DictPage();

    void queryWord(const QString &word);

signals:
    void queryWordFinished();

private:
    void handleData(const QString &word, const QString &ukPron, const QString &usPron, QString text);

private:
    YoudaoAPI *m_api;
    QVBoxLayout *m_layout;
    QLabel *m_wordLabel;
    QLabel *m_infoLabel;
    QLabel *m_ukLabel;
    QLabel *m_usLabel;
    DImageButton *m_ukPronButton;
    DImageButton *m_usPronButton;
};

#endif
