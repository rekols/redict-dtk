#ifndef CLICK_BOX_H
#define CLICK_BOX_H

#include <QWidget>

class ClickBox : public QWidget
{
    Q_OBJECT

public:
    ClickBox(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);

signals:
    void clicked();
};

#endif // CLICK_BOX_H
