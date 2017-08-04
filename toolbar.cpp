#include "toolbar.h"
#include <QHBoxLayout>
#include <QLabel>

ToolBar::ToolBar(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    QLabel *icon = new QLabel();
    edit = new QLineEdit();

    layout->setContentsMargins(0, 0, 0, 0);
    icon->setPixmap(QPixmap(":/resources/logo.svg").scaled(24, 24));
    edit->setFixedWidth(350);
    edit->setFixedHeight(25);

    layout->addSpacing(5);
    layout->addWidget(icon);
    layout->addSpacing(15);
    layout->addWidget(edit, 0, Qt::AlignHCenter);
    layout->addStretch();


    setFixedHeight(40);
}
