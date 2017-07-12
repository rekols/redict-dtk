#ifndef TRANSLATORPAGE_H
#define TRANSLATORPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPlainTextEdit>
#include <QKeyEvent>

#include "youdao_api.h"

class TranslatorPage : public QWidget
{
    Q_OBJECT

public:
    TranslatorPage(QWidget *parent = 0);

    QPlainTextEdit *original;

private:
    YoudaoAPI *api;
    QVBoxLayout *layout;
    QHBoxLayout *hLayout;
    QPlainTextEdit *translator;


protected:
    void keyPressEvent(QKeyEvent *);

private slots:
    void on_translator_clicked();
    void processingData(QString);
};

#endif // TRANSLATORPAGE_H
