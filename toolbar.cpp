#include "toolbar.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QSvgWidget>

ToolBar::ToolBar(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    edit = new QLineEdit();

    layout->setContentsMargins(0, 0, 0, 0);
    edit->setFixedWidth(350);
    edit->setFixedHeight(25);

    QSvgWidget *iconWidget = new QSvgWidget;
    iconWidget->load(QString(":/resources/logo.svg"));
    iconWidget->setFixedSize(24, 24);

    layout->addSpacing(5);
    layout->addWidget(iconWidget);
    layout->addSpacing(15);
    layout->addWidget(edit, 0, Qt::AlignHCenter);
    layout->addStretch();

    setFixedHeight(40);
}
