#include "float_box.h"
#include <QPainter>
#include <DBlurEffectWidget>

FloatBox::FloatBox(QWidget *parent)
    : DAbstractDialog(parent)
{
    DBlurEffectWidget *bgBlurWidget = new DBlurEffectWidget(this);
    bgBlurWidget->setBlendMode(DBlurEffectWidget::BehindWindowBlend);
    bgBlurWidget->setMaskColor(QColor("#404244"));

    layout = new QVBoxLayout(this);
    api = new YoudaoAPI(this);
    word = new QLabel();
    pron = new QLabel();
    content = new QLabel();

    word->setStyleSheet("QLabel { background-color : transparent; color : #FFFFFF; }");
    pron->setStyleSheet("QLabel { background-color : transparent; color : #FFFFFF; }");
    content->setStyleSheet("QLabel { background-color : transparent; color : #FFFFFF; }");

    QFont font;
    font.setPointSize(15);
    word->setFont(font);

    word->setWordWrap(true);
    content->setWordWrap(true);

    layout->addStretch();
    layout->addWidget(word);
    layout->addWidget(pron);
    layout->addSpacing(10);
    layout->addWidget(content);
    layout->addStretch();

    setAttribute(Qt::WA_DeleteOnClose, true);

    setFixedSize(300, 200);
    //setWindowFlags(Qt::FramelessWindowHint | Qt::ToolTip);
    bgBlurWidget->resize(size());

    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_AlwaysStackOnTop);

    connect(api, SIGNAL(searchWordFinished(QString,QString,QString,QString)), this, SLOT(replyFinished(QString,QString,QString,QString)));
}

void FloatBox::queryWord(const QString &text)
{
    api->searchWord(text);
}

void FloatBox::replyFinished(QString name, QString uk_phonetic, QString us_phonetic, QString text)
{
    if (!uk_phonetic.isEmpty()) {
        pron->setVisible(true);
        pron->setText(QString("英[%1]      美[%2]").arg(uk_phonetic).arg(us_phonetic));
    }else {
        pron->setVisible(false);
    }

    word->setText(name);
    content->setText(text);
}
