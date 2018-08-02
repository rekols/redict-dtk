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
#include "dthememanager.h"

#include <QHBoxLayout>
#include <QCompleter>
#include <QKeyEvent>
#include <QDebug>

QueryEdit::QueryEdit(QWidget *parent)
    : QLineEdit(parent),
      m_listView(new QListView(this)),
      m_listModel(new QStringListModel(this)),
      m_api(YoudaoAPI::instance()),
      m_closeBtn(new DImageButton(":/images/close_normal.svg",
                                  ":/images/close_hover.svg",
                                  ":/images/close_press.svg")),
      m_iconLabel(new QLabel),
      m_isEnter(false)
{
    QHBoxLayout *layout = new QHBoxLayout;
    setLayout(layout);

    m_iconLabel->setFixedSize(18, 18);
    m_closeBtn->hide();

    layout->addSpacing(3);
    layout->addWidget(m_iconLabel, 0, Qt::AlignLeft | Qt::AlignVCenter);
    layout->addWidget(m_closeBtn, 0, Qt::AlignRight | Qt::AlignVCenter);

    m_listView->setItemDelegate(new ListDelegate);
    m_listView->setWindowFlags(Qt::ToolTip);
    m_listView->setFixedHeight(145);

    setPlaceholderText("输入要查询的单词或词组");
    setFocusPolicy(Qt::StrongFocus);
    setTextMargins(30, 0, 30, 0);
    setObjectName("QueryEdit");
    setFixedHeight(35);
    initTheme();

    connect(this, &QLineEdit::textChanged,
            [=] {
                const QString text = this->text();

                if (text.isEmpty()) {
                    m_closeBtn->hide();
                    m_listView->hide();
                } else {
                    m_closeBtn->show();
                }

                if (!m_isEnter) {
                    m_api->suggest(text);
                }
            });

    connect(m_api, &YoudaoAPI::suggestFinished, this, &QueryEdit::handleSuggest);
    connect(m_closeBtn, &DImageButton::clicked, this, &QLineEdit::clear);

    connect(m_listView, &QListView::clicked, this,
            [=] (const QModelIndex &index) {
                QStringList data = index.data().toString().split(" | ");
                m_isEnter = true;
                setText(data.first());
                m_listView->hide();
            });

    connect(DThemeManager::instance(), &DThemeManager::themeChanged, this, &QueryEdit::initTheme);
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

void QueryEdit::initTheme()
{
    const qreal ratio = devicePixelRatioF();
    const bool isDark = DThemeManager::instance()->theme() == "dark";

    QPixmap iconPixmap;

    if (isDark) {
        iconPixmap = DSvgRenderer::render(":/images/search_dark.svg", QSize(12, 12) * ratio);
    } else {
        iconPixmap = DSvgRenderer::render(":/images/search_light.svg", QSize(12, 12) * ratio);
    }

    iconPixmap.setDevicePixelRatio(ratio);
    m_iconLabel->setPixmap(iconPixmap);
}

void QueryEdit::handleSuggest(const QStringList &list)
{
    const int rowCount = list.count();

    m_listModel->setStringList(list);
    m_listView->setModel(m_listModel);

    if (rowCount == 0) {
        m_listView->hide();
        return;
    }

    // adjust the height of listview.
    switch (rowCount) {
    case 1:
        m_listView->setFixedHeight(35 + 5);
        break;

    case 2:
        m_listView->setFixedHeight(35 * 2 + 5);
        break;

    case 3:
        m_listView->setFixedHeight(35 * 3 + 5);
        break;

    case 4:
        m_listView->setFixedHeight(35 * 4 + 5);
        break;
    }

    m_listView->setFixedWidth(width() - 40);
    QPoint p(0, height());
    int x = mapToGlobal(p).x() + 20;
    int y = mapToGlobal(p).y() + 1;
    m_listView->move(x, y);
    m_listView->show();
}
