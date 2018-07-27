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

#ifndef EVENTMONITOR_H
#define EVENTMONITOR_H

#include <QThread>
#include <QPoint>
#include <QDebug>
#include <QTimer>

#include <X11/Xlib.h>
#include <X11/extensions/record.h>

class EventMonitor : public QThread
{
    Q_OBJECT

public:
    EventMonitor(QObject *parent = nullptr);
    ~EventMonitor();

signals:
    void buttonPress(const int x, const int y);
    void selectionChanged();

protected:
    void run();
    static void callback(XPointer trash, XRecordInterceptData* data);
    void handleEvent(XRecordInterceptData* data);

private:
    void resetDoubleClick();

private:
    bool m_hoverFlag;
    bool m_doubleClickFlag;
    bool m_doubleClickTimeout;
    int m_doubleClickCounter;
};

#endif
