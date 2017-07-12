#include "translator_page.h"
#include <QLabel>
#include <QPushButton>

TranslatorPage::TranslatorPage(QWidget *parent)
    : QWidget(parent),
      api(new YoudaoAPI(this))
{
    layout = new QVBoxLayout;
    hLayout = new QHBoxLayout;
    original = new QPlainTextEdit;
    translator = new QPlainTextEdit;

    QLabel *tips1 = new QLabel("原文");
    QLabel *tips2 = new QLabel("译文");

    QPushButton *trBtn = new QPushButton("翻译");
    hLayout->addWidget(trBtn);

    translator->setReadOnly(true);

    layout->addWidget(tips1);
    layout->addWidget(original);
    layout->addSpacing(10);
    layout->addLayout(hLayout);
    layout->addSpacing(10);
    layout->addWidget(tips2);
    layout->addWidget(translator);

    setLayout(layout);

    tips1->setStyleSheet("color: #BCBCBC");
    tips2->setStyleSheet("color: #BCBCBC");
    this->setStyleSheet("QPlainTextEdit { border: 1px solid #505050; border-radius: 5px; font-size: 15px; padding: 5px;}");

    connect(trBtn, SIGNAL(clicked()), this, SLOT(on_translator_clicked()));
    connect(api, SIGNAL(translatorFinished(QString)), this, SLOT(processingData(QString)));
}

void TranslatorPage::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return && (event->modifiers() & Qt::ControlModifier))
            on_translator_clicked();
}

void TranslatorPage::on_translator_clicked()
{
    original->setFocus();

    if (!original->toPlainText().isEmpty()) {
        api->translator(original->toPlainText());
    }else {

    }
}

void TranslatorPage::processingData(QString text)
{
    translator->setPlainText(text);
}
