#include "main_window.h"
#include <DTitlebar>
#include <QApplication>
#include <QClipboard>
#include <QDebug>

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

    clickBox->hide();
    floatBox->hide();

    layout->addWidget(homePage);
    layout->addWidget(dictPage);
    layout->addWidget(trPage);

    mainWidget->setLayout(layout);

    this->titleBar()->setCustomWidget(toolbar, Qt::AlignVCenter, false);
    this->titleBar()->setWindowFlags(Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);
    this->setCentralWidget(mainWidget);

    connect(toolbar, SIGNAL(switchTab(int)), this, SLOT(switchTab(int)));

    setBorderColor("#5D5D5D");

    connect(qApp->clipboard(), &QClipboard::selectionChanged, [=]{
        clickBox->move(QCursor::pos().x()+15, QCursor::pos().y()+10);
        clickBox->show();
    });

    connect(clickBox, &ClickBox::clicked, this, [=]{
        QString word = qApp->clipboard()->text(QClipboard::Selection);
        floatBox->queryWord(word);
        floatBox->move(QCursor::pos().x(), QCursor::pos().y());
        floatBox->show();
    });

    connect(&eventMonitor, &EventMonitor::buttonPress, this, [=]{
        clickBox->hide();
        floatBox->hide();
    }, Qt::QueuedConnection);

    eventMonitor.start();
}

MainWindow::~MainWindow()
{

}

void MainWindow::closeEvent(QCloseEvent *)
{

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
