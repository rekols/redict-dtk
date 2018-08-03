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

#include "popupwindow.h"
#include "dsvgrenderer.h"
#include <QMouseEvent>
#include <QCloseEvent>
#include <QPainter>
#include <QDebug>

PopupWindow::PopupWindow(QWidget *parent)
    : QWidget(parent),
      m_layout(new QStackedLayout(this)),
      m_content(new PopupContent),
      m_regionInter(new DRegionMonitor(this)),
      m_api(new YoudaoAPI)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::ToolTip);
    setAttribute(Qt::WA_TranslucentBackground);
    setCursor(Qt::PointingHandCursor);
    setFixedSize(30, 30);

    QWidget::hide();

    connect(m_regionInter, &DRegionMonitor::buttonPress, this, &PopupWindow::onGlobMousePress);
    connect(m_api, &YoudaoAPI::searchFinished, m_content, &PopupContent::updateContent);
}

PopupWindow::~PopupWindow()
{
    delete m_content;
}

void PopupWindow::paintEvent(QPaintEvent *e)
{
    QWidget::paintEvent(e);

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);

    const qreal ratio = devicePixelRatioF();
    QPixmap pixmap = DSvgRenderer::render(":/images/redict.svg", QSize(30, 30) * ratio);
    pixmap.setDevicePixelRatio(ratio);

    painter.drawPixmap(rect(), pixmap);
}

void PopupWindow::mouseReleaseEvent(QMouseEvent *e)
{
    QWidget::mouseReleaseEvent(e);

    if (e->button() == Qt::LeftButton) {
        QPoint pos = QCursor::pos();
        QWidget::hide();

        m_content->show();
        m_content->move(pos);
    }
}

void PopupWindow::popup(const QPoint &pos)
{
    QWidget::move(QPoint(pos.x(), pos.y() - 40));
    QWidget::show();

    if (m_regionInter->registered()) {
        m_regionInter->unregisterRegion();
    } else {
        m_regionInter->registerRegion();
    }

    m_content->hide();
}

void PopupWindow::query(const QString &text)
{
    m_api->queryWord(text);
}

void PopupWindow::onGlobMousePress(const QPoint &mousePos, const int flag)
{
    Q_UNUSED(flag);

    if (m_content->isVisible()) {
        const QRect rect = QRect(m_content->pos(), m_content->size());
        if (rect.contains(mousePos))
            return;
    }

    const QRect rect = QRect(pos(), size());
    if (rect.contains(mousePos))
        return;

    if (m_regionInter->registered()) {
        m_regionInter->unregisterRegion();
    }


    m_content->hide();
    QWidget::hide();
}
