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

#ifndef QUERYEDIT_H
#define QUERYEDIT_H

#include <QLineEdit>
#include <QListView>
#include <QLabel>
#include <QStringListModel>
#include "youdaoapi.h"
#include "dsvgrenderer.h"
#include "dimagebutton.h"

DWIDGET_USE_NAMESPACE

class QueryEdit : public QLineEdit
{
    Q_OBJECT

public:
    QueryEdit(QWidget *parent = nullptr);
    ~QueryEdit();

protected:
    void keyPressEvent(QKeyEvent *);
    void focusInEvent(QFocusEvent *);
    void focusOutEvent(QFocusEvent *);

private:
    void initTheme();
    void handleSuggest(const QStringList &list);

private:
    QListView *m_listView;
    QStringListModel *m_listModel;
    YoudaoAPI *m_api;
    DImageButton *m_closeBtn;
    QLabel *m_iconLabel;
    bool m_isEnter;
};

#endif
