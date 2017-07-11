#include "dict_page.h"
#include <QByteArray>

DictPage::DictPage(QWidget *parent)
    : QWidget(parent)
{
    dialog = new DDialog("提示", "请输入您要查询的单词", this);
    audio1 = new QMediaPlayer;
    audio2 = new QMediaPlayer;
    http = new QNetworkAccessManager(this);
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

    pronButton1 = new DImageButton(":/image/play.svg", NULL, NULL);
    pronButton2 = new DImageButton(":/image/play.svg", NULL, NULL);

    pronButton1->setFixedSize(24, 24);
    pronButton2->setFixedSize(24, 24);
    searchButton->setFixedWidth(100);

    nameLabel->setWordWrap(true);
    infoLabel->setWordWrap(true);

    nameLabel->setStyleSheet("font-size: 22px; color:#2CA7F8;");
    pronLabel1->setStyleSheet("font-size: 13px");
    pronLabel2->setStyleSheet("font-size: 13px");
    infoLabel->setStyleSheet("font-size: 17px");

    searchLayout->addSpacing(15);
    searchLayout->addWidget(searchEdit);
    searchLayout->addWidget(searchButton);
    searchLayout->addSpacing(15);

    wordLayout->addSpacing(32);
    wordLayout->addWidget(nameLabel);
    wordLayout->addSpacing(32);

    infoLayout->addSpacing(34);
    infoLayout->addWidget(infoLabel);
    infoLayout->addSpacing(34);

    pronLayout->addSpacing(32);
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

    connect(http, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyfinished(QNetworkReply *)));

    connect(pronButton1, &DImageButton::clicked, this, [=]{
        audio1->play();
    });

    connect(pronButton2, &DImageButton::clicked, this, [=]{
        audio2->play();
    });

    connect(searchEdit, SIGNAL(returnPressed()), this, SLOT(start()));
    connect(searchButton, SIGNAL(clicked()), this, SLOT(start()));

    init();
}

void DictPage::start()
{
    if (!searchEdit->text().isEmpty()) {
        this->queryWord(searchEdit->text());
        searchEdit->setFocus();
    }
    else {
        dialog->exec();
        searchEdit->setFocus();
    }
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

    dialog->addButton("确定", true);
    dialog->setIcon(QIcon(":/image/logo.svg"));
}

void DictPage::queryWord(const QString &word)
{
    QNetworkRequest request;
    request.setUrl(QUrl("http://fanyi.youdao.com/openapi.do?keyfrom=YouDaoCV&key=659600698&type=data&doctype=json&version=1.1&q=" + word));
    http->get(request);
}

void DictPage::replyfinished(QNetworkReply *reply)
{
    QJsonDocument json;
    QJsonObject object, data;

    QByteArray wordInformation = reply->readAll();

    json = QJsonDocument::fromJson(wordInformation);

    if (!json.isNull())
    {
        object = json.object();
        data = object.value("basic").toObject();

        QString uk_phonetic = data.value("uk-phonetic").toString();
        QString us_phonetic = data.value("us-phonetic").toString();
        QString text = NULL;

        QJsonArray explain = data.value("explains").toArray();

        nameLabel->setText(object.value("query").toString());

        if (uk_phonetic.isEmpty() && us_phonetic.isEmpty()) {
            pronLabel1->setVisible(false);
            pronLabel2->setVisible(false);
            pronButton1->setVisible(false);
            pronButton2->setVisible(false);

            if (!data.value("phonetic").toString().isEmpty()) {
                nameLabel->setText(nameLabel->text() + " [" + data.value("phonetic").toString() + "]");
            }
        }else {
            pronLabel1->setVisible(true);
            pronLabel2->setVisible(true);
            pronButton1->setVisible(true);
            pronButton2->setVisible(true);

            pronLabel1->setText(QString("英[%1]").arg(uk_phonetic));
            pronLabel2->setText(QString("美[%1]").arg(us_phonetic));

            audio1->setMedia(QUrl("http://dict.youdao.com/dictvoice?type=1&audio=" + nameLabel->text()));
            audio2->setMedia(QUrl("http://dict.youdao.com/dictvoice?type=2&audio=" + nameLabel->text()));
        }

        if (explain.isEmpty()) {
            for (int i=0; i<object.value("translation").toArray().size(); ++i) {
                text.append(object.value("translation").toArray().at(i).toString());
                text.append("\n");
            }
        }else {
            for (int i=0; i<explain.size(); ++i) {
                text.append(explain.at(i).toString());
                text.append("\n");
            }
        }

        infoLabel->setText(text);
    }
}
