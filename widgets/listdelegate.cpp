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

#include "listdelegate.h"
#include "dthememanager.h"
#include <QPainter>

DWIDGET_USE_NAMESPACE

ListDelegate::ListDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{

}

ListDelegate::~ListDelegate()
{
}

void ListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const bool isDarkTheme = DThemeManager::instance()->theme() == "dark";
    const QStringList data = index.data().toString().split(" | ");
    const QString entry = data.first();
    const QString explain = data.last();
    const QRect rect = option.rect;

    // draw bottom line.
    if (index.row()) {
        if (isDarkTheme) {
            painter->setPen(QColor(255, 255, 255, 255 * 0.1));
        } else {
            painter->setPen(QColor(0, 0, 0, 255 * 0.1));
        }

        painter->drawLine(QPoint(rect.x(), rect.y() - 1),
                          QPoint(rect.width(), rect.y() - 1));
    }

    // draw background.
    if (option.state & QStyle::State_Selected) {
        painter->fillRect(rect, (isDarkTheme) ? QColor("#045998") : QColor("#D0E8FA"));
        painter->setPen((isDarkTheme) ? QColor("#FFFFFF") : QColor("#2CA7F8"));
    } else {

        if (isDarkTheme) {
            painter->setPen(Qt::white);
        } else {
            painter->setPen(Qt::black);
        }
    }

    // set fixed font size.
    QFont font = painter->font();
    font.setPointSize(11);
    painter->setFont(font);

    QRect entryRect = rect;
    entryRect.setLeft(10);
    entryRect.setWidth(rect.width() / 3);
    const QString entryText = painter->fontMetrics().elidedText(entry, Qt::ElideRight, rect.width() / 3 - 20);
    painter->drawText(entryRect, Qt::AlignLeft | Qt::AlignVCenter, entryText);

    QRect explainRect = rect;
    explainRect.setLeft(rect.width() / 3);
    explainRect.setRight(rect.right() - 10);
    const QString explainText = painter->fontMetrics().elidedText(explain, Qt::ElideRight, rect.width() - entryRect.width() - 20);
    painter->drawText(explainRect, Qt::AlignLeft | Qt::AlignVCenter, explainText);
}

QSize ListDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    return QSize(-1, 35);
}
