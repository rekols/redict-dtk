#include "toolbar.h"
#include <QKeyEvent>

ToolBar::ToolBar(QWidget *parent)
    : QWidget(parent)
{
    setFixedHeight(24);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    searchEdit = new DSearchEdit();
    searchEdit->setPlaceHolder("查单词");
    searchEdit->setFixedWidth(280);

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
