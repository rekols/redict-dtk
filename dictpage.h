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

#ifndef DICTPAGE_H
#define DICTPAGE_H

#include <QWidget>
#include <QLabel>
#include <QMediaPlayer>
#include "dimagebutton.h"
#include "youdaoapi.h"

DWIDGET_USE_NAMESPACE

class DictPage : public QWidget
{
    Q_OBJECT
    
public:
    DictPage(QWidget *parent = nullptr);
    ~DictPage();

    void queryWord(const QString &text);

private:
    void handleQueryFinished(std::tuple<QString, QString, QString, QString, QString>);

private:
    YoudaoAPI *m_api;
    QLabel *m_wordLabel;
    QLabel *m_infoLabel;
    QLabel *m_webLabel;
    QLabel *m_webTips;
    DImageButton *m_ukBtn;
    DImageButton *m_usBtn;
    QLabel *m_ukLabel;
    QLabel *m_usLabel;
    QMediaPlayer *m_audio;
};

#endif
