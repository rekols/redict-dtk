#ifndef TRANSLATORPAGE_H
#define TRANSLATORPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPlainTextEdit>

class TranslatorPage : public QWidget
{
    Q_OBJECT

public:
    TranslatorPage(QWidget *parent = 0);

private:
    QVBoxLayout *layout;
    QHBoxLayout *hLayout;
    QPlainTextEdit *original;
    QPlainTextEdit *translator;
};

#endif // TRANSLATORPAGE_H
