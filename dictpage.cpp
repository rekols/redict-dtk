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

#include "dictpage.h"
#include "scrollarea.h"
#include "dthememanager.h"
#include <QVBoxLayout>
#include <QScrollBar>

DictPage::DictPage(QWidget *parent)
    : QWidget(parent),
      m_api(YoudaoAPI::instance()),
      m_wordLabel(new QLabel),
      m_infoLabel(new QLabel),
      m_ukLabel(new QLabel),
      m_usLabel(new QLabel),
      m_ukBtn(new DImageButton),
      m_usBtn(new DImageButton),
      m_audio(new QMediaPlayer)
{
    ScrollArea *contentFrame = new ScrollArea;
    m_scrollArea = contentFrame;
    contentFrame->setWidgetResizable(true);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(contentFrame);
    layout->addSpacing(15);

    QWidget *contentWidget = new QWidget;
    QVBoxLayout *contentLayout = new QVBoxLayout(contentWidget);
    QHBoxLayout *phoneticLayout = new QHBoxLayout;

    phoneticLayout->addWidget(m_ukLabel);
    phoneticLayout->addSpacing(5);
    phoneticLayout->addWidget(m_ukBtn);
    phoneticLayout->addSpacing(70);
    phoneticLayout->addWidget(m_usLabel);
    phoneticLayout->addSpacing(5);
    phoneticLayout->addWidget(m_usBtn);
    phoneticLayout->addStretch();

    contentLayout->setSpacing(0);
    contentLayout->setContentsMargins(20, 0, 20, 0);
    contentLayout->addSpacing(8);
    contentLayout->addWidget(m_wordLabel);
    contentLayout->addSpacing(4);
    contentLayout->addLayout(phoneticLayout);
    contentLayout->addSpacing(6);
    contentLayout->addWidget(m_infoLabel);
    contentLayout->addStretch();

    contentFrame->setWidget(contentWidget);

    m_wordLabel->setWordWrap(true);
    m_infoLabel->setWordWrap(true);

    m_infoLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
    m_ukLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
    m_usLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);

    m_wordLabel->setStyleSheet("QLabel { color: #2CA7F8; font-size: 25px; font-weight: bold; }");
    m_infoLabel->setStyleSheet("QLabel { font-size: 16px; } ");

    initTheme();

    connect(DThemeManager::instance(), &DThemeManager::themeChanged, this, &DictPage::initTheme);

    connect(m_api, &YoudaoAPI::searchFinished, this, &DictPage::handleQueryFinished);

    connect(m_ukBtn, &DImageButton::clicked, this, [=]{
        m_audio->setMedia(QUrl("http://dict.youdao.com/dictvoice?type=1&audio=" + m_wordLabel->text()));
        m_audio->play();
    });

    connect(m_usBtn, &DImageButton::clicked, this, [=]{
        m_audio->setMedia(QUrl("http://dict.youdao.com/dictvoice?type=2&audio=" + m_wordLabel->text()));
        m_audio->play();
    });
}

DictPage::~DictPage()
{
}

void DictPage::queryWord(const QString &text)
{
    if (text == m_wordLabel->text()) {
        return;
    }

    m_scrollArea->verticalScrollBar()->setValue(0);
    m_api->queryWord(text);
}

void DictPage::initTheme()
{
    const bool isDark = DThemeManager::instance()->theme() == "dark";

    if (isDark) {
        m_ukBtn->setNormalPic(":/images/audio-dark-normal.svg");
        m_ukBtn->setHoverPic(":/images/audio-dark-hover.svg");
        m_ukBtn->setPressPic(":/images/audio-dark-press.svg");
        m_usBtn->setNormalPic(":/images/audio-dark-normal.svg");
        m_usBtn->setHoverPic(":/images/audio-dark-hover.svg");
        m_usBtn->setPressPic(":/images/audio-dark-press.svg");
    } else {
        m_ukBtn->setNormalPic(":/images/audio-light-normal.svg");
        m_ukBtn->setHoverPic(":/images/audio-light-hover.svg");
        m_ukBtn->setPressPic(":/images/audio-light-press.svg");
        m_usBtn->setNormalPic(":/images/audio-light-normal.svg");
        m_usBtn->setHoverPic(":/images/audio-light-hover.svg");
        m_usBtn->setPressPic(":/images/audio-light-press.svg");
    }
}

void DictPage::handleQueryFinished(std::tuple<QString, QString, QString, QString, QString> data)
{
    const QString &queryWord = std::get<0>(data);
    const QString &ukPhonetic = std::get<1>(data);
    const QString &usPhonetic = std::get<2>(data);
    const QString &basicExplains = std::get<3>(data);
    const QString &webReferences = std::get<4>(data);

    if (ukPhonetic.isEmpty()) {
        m_ukLabel->setVisible(false);
        m_ukBtn->setVisible(false);
    } else {
        m_ukLabel->setVisible(true);
        m_ukBtn->setVisible(true);
        m_ukLabel->setText(QString("英 [%1]").arg(ukPhonetic));
    }

    if (usPhonetic.isEmpty()) {
        m_usLabel->setVisible(false);
        m_usBtn->setVisible(false);
    } else {
        m_usLabel->setVisible(true);
        m_usBtn->setVisible(true);
        m_usLabel->setText(QString("美 [%1]").arg(usPhonetic));
    }

    m_wordLabel->setText(queryWord);

    QString text = basicExplains;

    if (!webReferences.isEmpty()) {
        text += "<br><b>网络释义</b></br>";
        text += webReferences;
    }

    m_infoLabel->setText(text);
}
