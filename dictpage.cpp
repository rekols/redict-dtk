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

#include "dictpage.h"

DictPage::DictPage(QWidget *parent)
    : QWidget(parent),
      m_contentFrame(new QWidget),
      m_contentLayout(new QVBoxLayout(m_contentFrame)),
      m_contentArea(new QScrollArea),
      m_api(new YoudaoAPI),
      m_wordLabel(new QLabel),
      m_infoLabel(new QLabel),
      m_ukLabel(new QLabel),
      m_usLabel(new QLabel),
      m_ukPronButton(new DImageButton(":/images/audio-volume-high-normal.svg",
                                      ":/images/audio-volume-high-hover.svg",
                                      ":/images/audio-volume-high-press.svg")),
      m_usPronButton(new DImageButton(":/images/audio-volume-high-normal.svg",
                                      ":/images/audio-volume-high-hover.svg",
                                      ":/images/audio-volume-high-press.svg")),
      m_mediaPlayer(new QMediaPlayer)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setMargin(0);
    mainLayout->addWidget(m_contentArea);

    m_contentArea->setContentsMargins(0, 0, 0, 0);
    m_contentArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_contentArea->setWidgetResizable(true);
    m_contentArea->setWidget(m_contentFrame);

    initUI();

    connect(m_api, &YoudaoAPI::finished, this, &DictPage::handleData);
    connect(m_ukPronButton, &DImageButton::clicked, this, [=] {
                                                              m_mediaPlayer->stop();
                                                              m_mediaPlayer->setMedia(QUrl("http://dict.youdao.com/dictvoice?type=1&audio=" + m_wordLabel->text()));
                                                              m_mediaPlayer->play();
                                                          });

    connect(m_usPronButton, &DImageButton::clicked, this, [=] {
                                                              m_mediaPlayer->stop();
                                                              m_mediaPlayer->setMedia(QUrl("http://dict.youdao.com/dictvoice?type=2&audio=" + m_wordLabel->text()));
                                                              m_mediaPlayer->play();
                                                          });

}

DictPage::~DictPage()
{
}

void DictPage::initUI()
{
    QHBoxLayout *pronLayout = new QHBoxLayout;
    pronLayout->addWidget(m_ukLabel);
    pronLayout->addSpacing(5);
    pronLayout->addWidget(m_ukPronButton);
    pronLayout->addSpacing(50);
    pronLayout->addWidget(m_usLabel);
    pronLayout->addSpacing(5);
    pronLayout->addWidget(m_usPronButton);
    pronLayout->addStretch();

    m_wordLabel->setObjectName("WordLabel");
    m_wordLabel->setWordWrap(true);
    m_infoLabel->setWordWrap(true);

    m_contentLayout->addWidget(m_wordLabel);
    m_contentLayout->addLayout(pronLayout);
    m_contentLayout->addSpacing(10);
    m_contentLayout->addWidget(m_infoLabel);
    m_contentLayout->addStretch();
    m_contentLayout->setContentsMargins(10, 0, 10, 0);
}

void DictPage::queryWord(const QString &word)
{
    if (!word.isEmpty()) {
        m_ukPronButton->hide();
        m_ukPronButton->hide();
        m_api->queryWord(word);
    }
}

void DictPage::handleData(const QString &word, const QString &ukPron, const QString &usPron, QString text)
{
    if (ukPron.isEmpty() && usPron.isEmpty()) {
        m_ukLabel->hide();
        m_usLabel->hide();
        m_ukPronButton->hide();
        m_usPronButton->hide();
    } else {
        m_ukLabel->show();
        m_usLabel->show();
        m_ukPronButton->show();
        m_usPronButton->show();

        m_ukLabel->setText(QString("英[%1]").arg(ukPron));
        m_usLabel->setText(QString("美[%1]").arg(usPron));
    }

    m_wordLabel->setText(word);
    m_infoLabel->setText(text);

    emit queryWordFinished();
}
