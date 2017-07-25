#include "click_box.h"
#include <QPainter>
#include <QMouseEvent>

ClickBox::ClickBox(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(35, 35);
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint | Qt::ToolTip);
}

void ClickBox::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.drawImage(rect(), QImage(":/image/logo.svg"));
}

void ClickBox::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked();
        this->setVisible(false);
    }
}
