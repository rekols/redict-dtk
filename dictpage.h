/*
 * Copyright (C) 2017 ~ 2017 Deepin Technology Co., Ltd.
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

#ifndef DICTPAGE_H
#define DICTPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QLabel>
#include <QMediaPlayer>
#include "youdaoapi.h"
#include "dimagebutton.h"

DWIDGET_USE_NAMESPACE

class DictPage : public QWidget
{
    Q_OBJECT

public:
    DictPage(QWidget *parent = nullptr);
    ~DictPage();

    void initUI();
    void queryWord(const QString &word);

signals:
    void queryWordFinished();

private:
    void handleData(const QString &word, const QString &ukPron, const QString &usPron, QString text);

private:
    QWidget *m_contentFrame;
    QVBoxLayout *m_contentLayout;
    QScrollArea *m_contentArea;
    YoudaoAPI *m_api;
    QLabel *m_wordLabel;
    QLabel *m_infoLabel;
    QLabel *m_ukLabel;
    QLabel *m_usLabel;
    DImageButton *m_ukPronButton;
    DImageButton *m_usPronButton;
    QMediaPlayer *m_mediaPlayer;
};

#endif
