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

#include "textedit.h"
#include <QFocusEvent>

TextEdit::TextEdit(QWidget *parent)
    : QPlainTextEdit(parent)
{

}

TextEdit::~TextEdit()
{
}

void TextEdit::clearSelection()
{
    QTextCursor cursor = textCursor();
    cursor.clearSelection();
    setTextCursor(cursor);
}

void TextEdit::focusInEvent(QFocusEvent *e)
{
    QPlainTextEdit::focusInEvent(e);

    emit focusIn();
}

void TextEdit::focusOutEvent(QFocusEvent *e)
{
    QPlainTextEdit::focusOutEvent(e);

    emit focusOut();
}
