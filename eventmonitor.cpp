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

#include "eventmonitor.h"
#include <X11/Xlibint.h>

EventMonitor::EventMonitor(QObject *parent)
    : QThread(parent)
{
    m_hoverFlag = false;
    m_doubleClickFlag = false;
    m_doubleClickTimeout = true;
    m_doubleClickCounter = 0;
}

EventMonitor::~EventMonitor()
{
    requestInterruption();
    quit();
    wait();
}

void EventMonitor::run()
{
    if (isInterruptionRequested())
        return;

    Display *display = XOpenDisplay(0);

    // unable to open display.
    if (display == 0) {
        return;
    }

    XRecordClientSpec clients = XRecordAllClients;
    XRecordRange *range = XRecordAllocRange();
    // unable to allocate XRecordRange
    if (range == 0) {
        return;
    }

    memset(range, 0, sizeof(XRecordRange));
    range->device_events.first = KeyPress;
    range->device_events.last = MotionNotify;

    XRecordContext context = XRecordCreateContext(display, 0, &clients, 1, &range, 1);
    if (context == 0) {
        return;
    }
    XFree(range);

    XSync(display, True);

    Display *display_datalink = XOpenDisplay(0);
    if (display_datalink == 0) {
        return;
    }

    if (!XRecordEnableContext(display_datalink, context, callback, (XPointer) this)) {
        return;
    }
}

void EventMonitor::callback(XPointer ptr, XRecordInterceptData* data)
{
    ((EventMonitor *) ptr)->handleEvent(data);
}

void EventMonitor::handleEvent(XRecordInterceptData* data)
{
    if (data->category == XRecordFromServer) {
        xEvent *event = (xEvent *)data->data;

        switch (event->u.u.type) {
        case ButtonPress:
            Q_EMIT buttonPress(event->u.keyButtonPointer.rootX,
                               event->u.keyButtonPointer.rootY);

            if (event->u.u.detail == 1) {
                m_hoverFlag = false;

                if (m_doubleClickTimeout) {
                    m_doubleClickFlag = false;
                    m_doubleClickTimeout = false;
                    m_doubleClickCounter = 0;
                }
            }

            break;

        case ButtonRelease:
            if (event->u.u.detail == 1) {
                m_doubleClickCounter += 1;

                if (m_doubleClickCounter == 2) {
                    m_doubleClickFlag = true;
                    m_doubleClickTimeout = true;;
                }

                if (m_hoverFlag || m_doubleClickFlag) {
                    qDebug() << "!!!!";
                    Q_EMIT selectionChanged();
                }

                m_hoverFlag = false;
            }
            break;

        case MotionNotify:
            m_hoverFlag = true;
            break;
        }
    }

    fflush(stdout);
    XRecordFreeData(data);
}

void EventMonitor::resetDoubleClick()
{
    m_doubleClickFlag = false;
    m_doubleClickTimeout = true;
}
