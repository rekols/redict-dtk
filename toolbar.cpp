#include "toolbar.h"
#include <QKeyEvent>
#include <QLabel>

ToolBar::ToolBar(QWidget *parent)
    : QWidget(parent)
{
    setFixedHeight(30);

    layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    search = new QLineEdit();

    search->setFixedWidth(340);
    search->setFixedHeight(25);

    QPixmap iconPixmap = QPixmap(":/image/logo.svg");
    iconLabel = new QLabel();
    iconLabel->setFixedSize(24, 24);
    iconLabel->setScaledContents(true);
    iconLabel->setPixmap(iconPixmap);

    returnButton = new DImageButton(
        ":/image/return_normal.png",
        ":/image/return_hover.png",
        ":/image/return_press.png"
        );
    returnButton->setFixedSize(24, 24);

    title = new QLabel("Rekols词典");

    layout->addWidget(iconLabel);
    layout->addWidget(title);
    layout->addWidget(returnButton);
    layout->addStretch();
    layout->addWidget(search);
    layout->addStretch();

    returnButton->setVisible(false);
    search->setVisible(false);
}

void ToolBar::showReturn()
{
    iconLabel->setVisible(false);
    title->setVisible(false);
    returnButton->setVisible(true);
    search->setVisible(true);
}

void ToolBar::showIcon()
{
    iconLabel->setVisible(true);
    title->setVisible(true);
    returnButton->setVisible(false);
    search->setVisible(false);
}

ToolBar::~ToolBar()
{

}
