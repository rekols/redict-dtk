#include "float_box.h"
#include <QPainter>
#include <DBlurEffectWidget>
#include <QEvent>

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
    content = new QPlainTextEdit();

    content->setObjectName("FloatText");
    content->setReadOnly(true);
    content->setFocusPolicy(Qt::NoFocus);

    word->setStyleSheet("QLabel { background-color : transparent; color : #FFFFFF; }");
    pron->setStyleSheet("QLabel { background-color : transparent; color : #FFFFFF; }");

    word->setWordWrap(true);

    layout->setMargin(10);
    layout->addStretch();
    layout->addWidget(word);
    layout->addWidget(pron);
    layout->setSpacing(10);
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

void FloatBox::leaveEvent(QEvent *e)
{

}

void FloatBox::queryWord(const QString &text)
{
    api->searchWord(text);

    initFontSize(text.length());
}

void FloatBox::initFontSize(const int &length)
{
    QFont font;

    if (length < 20) {
        font.setPointSize(18);
        word->setFont(font);
    }else if (length > 20 && length < 30) {
        font.setPointSize(15);
        word->setFont(font);
    }

    word->setFont(font);
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
    content->setPlainText(text);
}
