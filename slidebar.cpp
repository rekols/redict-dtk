#include "slidebar.h"
#include <QPainter>
#include <QMouseEvent>

SlideBar::SlideBar(QWidget *parent)
    : QWidget(parent)
{
    m_rowHeight = 40;
    m_currentIndex = 0;

    m_listItems << "查词" << "翻译";
    setFixedWidth(145);
}

void SlideBar::paintEvent(QPaintEvent *e)
{
    QWidget::paintEvent(e);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#FBFBFB"));
    painter.drawRect(rect());

    int count = 0;
    for (const QString &itemStr : m_listItems) {
        const bool isSelected = m_currentIndex == count;
        QPainterPath itemPath;
        itemPath.addRect(0, count * m_rowHeight, rect().width() - 1, m_rowHeight);

        if (isSelected) {
            painter.setPen(QColor(44, 167, 158));
            painter.fillPath(itemPath, QColor(44, 167, 158, 255 * 0.15));

            QPainterPath sepPath;
            sepPath.addRect(1, count * m_rowHeight, 3, m_rowHeight);
            painter.fillPath(sepPath, QColor(44, 167, 158));

            QPainterPath topSepPath;
            topSepPath.addRect(1, count * m_rowHeight, rect().width(), 1);
            painter.fillPath(topSepPath, QColor(44, 167, 158, 255 * 0.2));

            QPainterPath bottomSepPath;
            bottomSepPath.addRect(1, count * m_rowHeight + m_rowHeight - 1, rect().width(), 1);
            painter.fillPath(bottomSepPath, QColor(44, 167, 158, 255 * 0.2));

        } else {
            painter.setPen("#202020");
        }

        painter.drawText(QRect(0, count * m_rowHeight, rect().width(), m_rowHeight), Qt::AlignCenter, itemStr);

        ++count;
    }

    painter.setPen(QColor(230, 230, 230));
    painter.drawLine(QPoint(rect().width(), 0),
                     QPoint(rect().width(), rect().height()));
}

void SlideBar::mouseMoveEvent(QMouseEvent *e)
{
    const int index = e->y() / m_rowHeight;

    if (index >= m_listItems.count()) {
        QWidget::mouseMoveEvent(e);
    }
}

void SlideBar::mousePressEvent(QMouseEvent *e)
{
    const int index = e->y() / m_rowHeight;

    if (index < m_listItems.count() && m_currentIndex != index) {
        m_currentIndex = index;
        update();

        emit currentIndexChanged(m_currentIndex);
    }
}

void SlideBar::mouseReleaseEvent(QMouseEvent *e)
{

}
