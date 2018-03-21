/*
 * Copyright (C) 2017 ~ 2018 Deepin Technology Co., Ltd.
 *
 * Author:     rekols <rekols@foxmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef POPUPWINDOW_H
#define POPUPWINDOW_H

#include <QWidget>
#include <QStackedLayout>
#include "dregionmonitor.h"
#include "popupcontent.h"

DWIDGET_USE_NAMESPACE

class PopupWindow : public QWidget
{
    Q_OBJECT

public:
    PopupWindow(QWidget *parent = nullptr);
    ~PopupWindow();

protected:
    void paintEvent(QPaintEvent *);
    void mouseReleaseEvent(QMouseEvent *);

public slots:
    void popup(const QPoint &pos);

private:
    void onGlobMousePress(const QPoint &mousePos, const int flag);

private:
    QStackedLayout *m_layout;
    PopupContent *m_content;
    DRegionMonitor *m_regionInter;
};

#endif
