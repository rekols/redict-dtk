#include "main_window.h"
#include <DTitlebar>
#include <QTabBar>

MainWindow::MainWindow(QWidget *parent)
    : DMainWindow(parent)
{
    mainWidget = new QTabWidget();
    toolbar = new TabBar();
    homePage = new HomePage();
    dictPage = new DictPage();
    trPage = new TranslatorPage();

    mainWidget->addTab(homePage, "Home");
    mainWidget->addTab(dictPage, "Dictionary");
    mainWidget->addTab(trPage, "Translator");
    mainWidget->tabBar()->hide();
    mainWidget->setCurrentIndex(0);

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
    mainWidget->setCurrentIndex(index);

    if (index == 1) {
        dictPage->searchEdit->setFocus();
    }else if (index == 2) {
        trPage->original->setFocus();
    }
}
