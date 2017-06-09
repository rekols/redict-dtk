#ifndef LOADPROGRESS_H
#define LOADPROGRESS_H

#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QPixmap>
#include <QRect>
#include <QFont>
#include <QPointF>

class LoadProgress : public QWidget
{
public:
    LoadProgress(QWidget *parent = 0);
};

#endif // LOADPROGRESS_H
