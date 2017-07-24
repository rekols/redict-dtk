#include "dict_page.h"
#include <QByteArray>

DictPage::DictPage(QWidget *parent)
    : QWidget(parent),
      api(new YoudaoAPI(this))
{
    audio = new QMediaPlayer;
    layout = new QVBoxLayout(this);
    searchLayout = new QHBoxLayout();
    wordLayout = new QHBoxLayout();
    pronLayout = new QHBoxLayout();
    infoLayout = new QHBoxLayout();
    youdaoLayout = new QHBoxLayout();
    searchEdit = new QLineEdit();
    searchButton = new QPushButton("查询");
    nameLabel = new QLabel("");
    pronLabel1 = new QLabel("");
    pronLabel2 = new QLabel("");
    infoLabel = new QLabel("");

    searchEdit->setFixedHeight(35);
    searchButton->setFixedHeight(35);

    pronButton1 = new DImageButton(":/image/play.svg", NULL, NULL);
    pronButton2 = new DImageButton(":/image/play.svg", NULL, NULL);

    pronButton1->setFixedSize(24, 24);
    pronButton2->setFixedSize(24, 24);

    nameLabel->setWordWrap(true);
    infoLabel->setWordWrap(true);

    nameLabel->setStyleSheet("font-size: 22px; color:#2CA7F8;");
    pronLabel1->setStyleSheet("font-size: 13px");
    pronLabel2->setStyleSheet("font-size: 13px");
    infoLabel->setStyleSheet("font-size: 17px");

    searchLayout->addSpacing(15);
    searchLayout->addWidget(searchEdit);
    searchLayout->addSpacing(5);
    searchLayout->addWidget(searchButton);
    searchLayout->addSpacing(15);

    wordLayout->addSpacing(25);
    wordLayout->addWidget(nameLabel);
    wordLayout->addSpacing(25);

    infoLayout->addSpacing(28);
    infoLayout->addWidget(infoLabel);
    infoLayout->addSpacing(28);

    pronLayout->addSpacing(25);
    pronLayout->addWidget(pronButton1);
    pronLayout->addWidget(pronLabel1);
    pronLayout->addSpacing(5);
    pronLayout->addWidget(pronButton2);
    pronLayout->addWidget(pronLabel2);

    layout->addSpacing(10);
    layout->addLayout(searchLayout);
    layout->addSpacing(20);
    layout->addLayout(wordLayout);
    layout->addLayout(pronLayout);
    layout->addSpacing(12);
    layout->addLayout(infoLayout);
    layout->addStretch();
    layout->addLayout(youdaoLayout);
    layout->addSpacing(20);

    connect(pronButton1, &DImageButton::clicked, this, [=]{
        audio->setMedia(QUrl("http://dict.youdao.com/dictvoice?type=1&audio=" + nameLabel->text()));
        audio->play();
    });

    connect(pronButton2, &DImageButton::clicked, this, [=]{
        audio->setMedia(QUrl("http://dict.youdao.com/dictvoice?type=2&audio=" + nameLabel->text()));
        audio->play();
    });

    connect(searchEdit, SIGNAL(returnPressed()), this, SLOT(start()));
    connect(searchButton, SIGNAL(clicked()), this, SLOT(start()));

    connect(api, SIGNAL(searchWordFinished(QString, QString, QString, QString)), this, SLOT(processingData(QString, QString, QString, QString)));

    init();
}

void DictPage::start()
{
    if (!searchEdit->text().isEmpty()) {
        searchEdit->setFocus();
        api->searchWord(searchEdit->text());
    }
    else {
        searchEdit->setFocus();
    }
}

void DictPage::processingData(QString name, QString uk_phonetic, QString us_phonetic, QString text)
{
    if (uk_phonetic.isEmpty() && us_phonetic.isEmpty()) {
        pronLabel1->setVisible(false);
        pronLabel2->setVisible(false);
        pronButton1->setVisible(false);
        pronButton2->setVisible(false);
    }else {
        pronLabel1->setVisible(true);
        pronLabel2->setVisible(true);
        pronButton1->setVisible(true);
        pronButton2->setVisible(true);

        pronLabel1->setText(QString("英[%1]").arg(uk_phonetic));
        pronLabel2->setText(QString("美[%1]").arg(us_phonetic));
    }

    nameLabel->setText(name);
    infoLabel->setText(text);
}

void DictPage::init()
{
    QPixmap iconPixmap = QPixmap(":/image/youdao-dict.svg");
    QLabel *iconLabel = new QLabel;
    iconLabel->setFixedSize(20, 20);
    iconLabel->setScaledContents(true);
    iconLabel->setPixmap(iconPixmap);

    QLabel *tips = new QLabel("数据来自有道词典");
    tips->setStyleSheet("QLabel {font-size: 12px; }");

    youdaoLayout->addSpacing(15);
    youdaoLayout->addWidget(iconLabel);
    youdaoLayout->addWidget(tips);

    pronLabel1->setVisible(false);
    pronLabel2->setVisible(false);
    pronButton1->setVisible(false);
    pronButton2->setVisible(false);

    searchEdit->setFocus();
}
