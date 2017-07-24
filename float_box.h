#ifndef FLOAT_BOX_H
#define FLOAT_BOX_H

#include <QWidget>
#include <QVBoxLayout>
#include "youdao_api.h"
#include <QLabel>
#include <dabstractdialog.h>
#include <QPlainTextEdit>

DWIDGET_USE_NAMESPACE

class FloatBox : public DAbstractDialog
{
    Q_OBJECT

public:
    FloatBox(QWidget *parent = 0);

    void queryWord(const QString &text);
    void initFontSize(const int &length);

protected:
    void leaveEvent(QEvent *);

private slots:
    void replyFinished(QString, QString, QString, QString);

private:
    QVBoxLayout *layout;
    YoudaoAPI *api;

    QLabel *word;
    QLabel *pron;
    QPlainTextEdit *content;
};

#endif // FLOAT_BOX_H
