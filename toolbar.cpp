#include "toolbar.h"
#include <QKeyEvent>

ToolBar::ToolBar(QWidget *parent)
    : QWidget(parent)
{
    setFixedHeight(24);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    QPixmap iconPixmap = QPixmap(":/image/logo.svg");
    QLabel *iconLabel = new QLabel();
    iconLabel->setFixedSize(24, 24);
    iconLabel->setScaledContents(true);
    iconLabel->setPixmap(iconPixmap);

    searchEdit = new DSearchEdit();
    searchEdit->setPlaceHolder("查单词");
    searchEdit->setFixedWidth(280);

    layout->addWidget(iconLabel);
    layout->addSpacing(90);
    layout->addStretch();
    layout->addWidget(searchEdit, 0, Qt::AlignHCenter);
    layout->addStretch();
}

ToolBar::~ToolBar()
{
    delete searchEdit;
}

void ToolBar::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
    {
        emit searchWord(searchEdit->text());
    }
}
