#include "main_window.h"
#include <DTitlebar>

MainWindow::MainWindow(QWidget *parent)
    : DMainWindow(parent)
{
    mainWidget = new QWidget();
    layout = new QStackedLayout;
    toolbar = new TabBar();
    homePage = new HomePage();
    dictPage = new DictPage();
    trPage = new TranslatorPage();

    layout->addWidget(homePage);
    layout->addWidget(dictPage);
    layout->addWidget(trPage);

    mainWidget->setLayout(layout);

    this->titleBar()->setCustomWidget(toolbar, Qt::AlignVCenter, false);
    this->titleBar()->setWindowFlags(Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);
    this->setCentralWidget(mainWidget);

    connect(toolbar, SIGNAL(switchTab(int)), this, SLOT(switchTab(int)));

    setBorderColor("#5D5D5D");

}

MainWindow::~MainWindow()
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
