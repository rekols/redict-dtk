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

#include "queryedit.h"
#include "listdelegate.h"
#include <QCompleter>
#include <QKeyEvent>
#include <QDebug>

QueryEdit::QueryEdit(QWidget *parent)
    : QLineEdit(parent),
      m_listView(new QListView(this)),
      m_listModel(new QStringListModel(this)),
      m_api(YoudaoAPI::instance()),
      m_isEnter(false)
{
    m_listView->setItemDelegate(new ListDelegate);
    m_listView->setWindowFlags(Qt::ToolTip);
    m_listView->setFixedHeight(145);

    setPlaceholderText("输入要查询的单词或词组");
    setFocusPolicy(Qt::StrongFocus);
    setTextMargins(10, 0, 10, 0);
    setObjectName("QueryEdit");
    setFixedHeight(35);

    connect(this, &QLineEdit::textChanged,
            [=] {
                if (!m_isEnter) {
                    m_api->suggest(text());
                }
            });

    connect(m_api, &YoudaoAPI::suggestFinished, this, &QueryEdit::handleSuggest);
}

QueryEdit::~QueryEdit()
{
}

void QueryEdit::keyPressEvent(QKeyEvent *e)
{
    if (m_listView->isHidden()) {
        m_isEnter = false;
        QLineEdit::keyPressEvent(e);
    } else {
        QModelIndex currentIndex = m_listView->currentIndex();
        int count = m_listView->model()->rowCount();

        if (e->key() == Qt::Key_Down) {

            int row = currentIndex.row() + 1;
            if (row >= count) {
                row = 0;
            }

            QModelIndex index = m_listView->model()->index(row, 0);
            m_listView->setCurrentIndex(index);

        } else if (e->key() == Qt::Key_Up) {

            int row = currentIndex.row() - 1;
            if (row >= count || row < 0) {
                row = 0;
            }

            QModelIndex index = m_listView->model()->index(row, 0);
            m_listView->setCurrentIndex(index);

        } else if (e->key() == Qt::Key_Escape) {
            m_listView->hide();
        } else if (e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return) {

            m_isEnter = true;
            if (currentIndex.isValid()) {
                QStringList data = currentIndex.data().toString().split(" | ");
                setText(data.first());
            }
            m_listView->hide();

        } else {
            m_isEnter = false;
            m_listView->hide();
            QLineEdit::keyPressEvent(e);
        }
    }
}

void QueryEdit::focusInEvent(QFocusEvent *e)
{
    QLineEdit::focusInEvent(e);
}

void QueryEdit::focusOutEvent(QFocusEvent *e)
{
    QLineEdit::focusOutEvent(e);
    m_listView->hide();
}

void QueryEdit::handleSuggest(const QStringList &list)
{
    m_listModel->setStringList(list);
    m_listView->setModel(m_listModel);

    if (m_listModel->rowCount() == 0) {
        return;
    }

    m_listView->setFixedWidth(width());
    QPoint p(0, height());
    int x = mapToGlobal(p).x() + 2;
    int y = mapToGlobal(p).y() + 1;
    m_listView->move(x, y);
    m_listView->show();
}
