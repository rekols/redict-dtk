#ifndef FLOAT_BOX_H
#define FLOAT_BOX_H

#include <QWidget>
#include <QVBoxLayout>
#include "youdao_api.h"
#include <QLabel>

class FloatBox : public QWidget
{
    Q_OBJECT

public:
    FloatBox(QWidget *parent = 0);

    void queryWord(const QString &text);

private slots:
    void replyFinished(QString, QString, QString, QString);

private:
    QVBoxLayout *layout;
    YoudaoAPI *api;

    QLabel *word;
    QLabel *content;
};

#endif // FLOAT_BOX_H
