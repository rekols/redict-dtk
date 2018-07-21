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
#include <QVBoxLayout>
#include <QScrollArea>

DictPage::DictPage(QWidget *parent)
    : QWidget(parent),
      m_api(new YoudaoAPI),
      m_wordLabel(new QLabel),
      m_infoLabel(new QLabel),
      m_webLabel(new QLabel),
      m_webTips(new QLabel("网络释义")),
      m_ukLabel(new QLabel),
      m_usLabel(new QLabel),
      m_ukBtn(new DImageButton(":/images/audio-volume-high-normal.svg",
                               ":/images/audio-volume-high-hover.svg",
                               ":/images/audio-volume-high-press.svg")),
      m_usBtn(new DImageButton(":/images/audio-volume-high-normal.svg",
                               ":/images/audio-volume-high-hover.svg",
                               ":/images/audio-volume-high-press.svg")),
      m_audio(new QMediaPlayer)
{
    QScrollArea *contentFrame = new QScrollArea;
    contentFrame->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    contentFrame->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    contentFrame->setFocusPolicy(Qt::NoFocus);
    contentFrame->setWidgetResizable(true);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 10);
    layout->addWidget(contentFrame);

    QWidget *contentWidget = new QWidget;
    QVBoxLayout *contentLayout = new QVBoxLayout(contentWidget);
    QHBoxLayout *phoneticLayout = new QHBoxLayout;

    phoneticLayout->addWidget(m_ukLabel);
    phoneticLayout->addWidget(m_ukBtn);
    phoneticLayout->addSpacing(70);
    phoneticLayout->addWidget(m_usLabel);
    phoneticLayout->addWidget(m_usBtn);
    phoneticLayout->addStretch();

    contentLayout->setMargin(0);
    contentLayout->addWidget(m_wordLabel);
    contentLayout->addLayout(phoneticLayout);
    contentLayout->addSpacing(5);
    contentLayout->addWidget(m_infoLabel);
    contentLayout->addWidget(m_webTips);
    contentLayout->addSpacing(5);
    contentLayout->addWidget(m_webLabel);
    contentLayout->addStretch();

    contentFrame->setWidget(contentWidget);

    m_wordLabel->setWordWrap(true);
    m_infoLabel->setWordWrap(true);
    m_webLabel->setWordWrap(true);

    m_webTips->setStyleSheet("QLabel { font-size: 18px; font-weight: bold; }");
    m_wordLabel->setStyleSheet("QLabel { font-size: 25px; font-weight: bold; }");
    m_infoLabel->setStyleSheet("QLabel { font-size: 16px; } ");

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
    m_api->queryWord(text);
}

void DictPage::handleQueryFinished(std::tuple<QString, QString, QString, QString, QString> data)
{
    const QString &queryWord = std::get<0>(data);
    const QString &ukPhonetic = std::get<1>(data);
    const QString &usPhonetic = std::get<2>(data);
    const QString &basicExplains = std::get<3>(data);
    const QString &webReferences = std::get<4>(data);

    if (ukPhonetic.isEmpty() && usPhonetic.isEmpty()) {
        m_ukLabel->setVisible(false);
        m_usLabel->setVisible(false);
        m_ukBtn->setVisible(false);
        m_usBtn->setVisible(false);
    } else {
        m_ukLabel->setVisible(true);
        m_usLabel->setVisible(true);
        m_ukBtn->setVisible(true);
        m_usBtn->setVisible(true);

        m_ukLabel->setText(QString("英 [%1]").arg(ukPhonetic));
        m_usLabel->setText(QString("美 [%1]").arg(usPhonetic));
    }

    if (webReferences.isEmpty()) {
        m_webTips->setVisible(false);
    } else {
        m_webTips->setVisible(true);
    }

    m_wordLabel->setText(queryWord);
    m_infoLabel->setText(basicExplains);
    m_webLabel->setText(webReferences);
}
