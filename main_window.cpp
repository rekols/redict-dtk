#include "main_window.h"
#include <DTitlebar>
#include <QApplication>
#include <QClipboard>
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent)
    : DMainWindow(parent)
{
    mainWidget = new QWidget();
    layout = new QStackedLayout;
    toolbar = new TabBar();
    homePage = new HomePage();
    dictPage = new DictPage();
    trPage = new TranslatorPage();
    clickBox = new ClickBox(this);
    floatBox = new FloatBox(this);

    clickBox->setVisible(false);
    floatBox->setVisible(false);

    layout->addWidget(homePage);
    layout->addWidget(dictPage);
    layout->addWidget(trPage);
    layout->setCurrentIndex(1);

    mainWidget->setLayout(layout);

    this->titleBar()->setCustomWidget(toolbar, Qt::AlignVCenter, false);
    this->titleBar()->setWindowFlags(Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);
    this->setCentralWidget(mainWidget);

    connect(toolbar, SIGNAL(switchTab(int)), this, SLOT(switchTab(int)));

    setBorderColor("#5D5D5D");

    connect(qApp->clipboard(), &QClipboard::selectionChanged, [=]{
        if (!qApp->clipboard()->text(QClipboard::Selection).isEmpty()) {
            clickBox->move(QCursor::pos().x() + 15, QCursor::pos().y() + 10);
            clickBox->setVisible(true);
        }
    });

    connect(clickBox, &ClickBox::clicked, this, [=]{
        QString word = qApp->clipboard()->text(QClipboard::Selection);
        floatBox->queryWord(word);

        floatBox->move(QCursor::pos());
        floatBox->setVisible(true);
    });

    connect(&eventMonitor, &EventMonitor::buttonPress, this, [=]{
        clickBox->setVisible(false);
        floatBox->setVisible(false);
    }, Qt::QueuedConnection);

    connect(&eventMonitor, &EventMonitor::keyPress, this, [=]{
        clickBox->setVisible(false);
        floatBox->setVisible(false);
    }, Qt::QueuedConnection);

    eventMonitor.start();
}

MainWindow::~MainWindow()
{
    clickBox->deleteLater();
    floatBox->deleteLater();
}

void MainWindow::switchTab(int index)
{
    layout->setCurrentIndex(index);

    if (index == 1) {
        dictPage->searchEdit->setFocus();
    }else if (index == 2) {
        trPage->original->setFocus();
    }
}
