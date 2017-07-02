#include "toolbar.h"
#include <QKeyEvent>
#include <QLabel>

ToolBar::ToolBar(QWidget *parent)
    : QWidget(parent)
{
    setFixedHeight(25);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    QPixmap iconPixmap = QPixmap(":/image/logo.svg");
    QLabel *iconLabel = new QLabel();
    iconLabel->setFixedSize(24, 24);
    iconLabel->setScaledContents(true);
    iconLabel->setPixmap(iconPixmap);

    QLabel *title = new QLabel("Rekols词典");

    layout->addWidget(iconLabel);
    layout->addWidget(title);
    layout->addStretch();
    layout->addStretch();
}

ToolBar::~ToolBar()
{

}
