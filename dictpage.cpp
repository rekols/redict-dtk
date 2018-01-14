#include "dictpage.h"

DictPage::DictPage(QWidget *parent)
    : QWidget(parent),
      m_api(new YoudaoAPI),
      m_layout(new QVBoxLayout(this)),
      m_wordLabel(new QLabel),
      m_infoLabel(new QLabel),
      m_ukLabel(new QLabel),
      m_usLabel(new QLabel),
      m_ukPronButton(new DImageButton(":/images/audio-volume-high-normal.svg",
                                      ":/images/audio-volume-high-hover.svg",
                                      ":/images/audio-volume-high-press.svg")),
      m_usPronButton(new DImageButton(":/images/audio-volume-high-normal.svg",
                                      ":/images/audio-volume-high-hover.svg",
                                      ":/images/audio-volume-high-press.svg"))
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

    m_wordLabel->setStyleSheet("QLabel {"
                               "color: rgb(44, 167, 158);"
                               "font-size: 25px;"
                               "font-weight: 500;"
                               "}");
    m_wordLabel->setWordWrap(true);
    m_infoLabel->setWordWrap(true);

    m_layout->addWidget(m_wordLabel);
    m_layout->addLayout(pronLayout);
    m_layout->addSpacing(10);
    m_layout->addWidget(m_infoLabel);
    m_layout->addStretch();
    m_layout->setContentsMargins(20, 10, 20, 0);

    connect(m_api, &YoudaoAPI::finished, this, &DictPage::handleData);
}

DictPage::~DictPage()
{
}

void DictPage::queryWord(const QString &word)
{
    if (!word.isEmpty()) {
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
