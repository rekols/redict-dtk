#include "translator_page.h"
#include <QLabel>
#include <QPushButton>

TranslatorPage::TranslatorPage(QWidget *parent)
    :QWidget(parent)
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

    this->setStyleSheet("QPlainTextEdit { border: 1px solid #5E5E5E; }");
}
