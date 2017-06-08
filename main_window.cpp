#include "main_window.h"
#include <DTitlebar>
#include "home_page.h"
#include <QTabBar>

MainWindow::MainWindow(QWidget *parent)
    : DMainWindow(parent)
{
    mainWidget = new QTabWidget();
    toolbar = new ToolBar();
    loadingPage = new LoadingPage();
    homePage = new HomePage();
    dictPage = new DictPage();

    mainWidget->addTab(loadingPage, "LoadPage");
    mainWidget->addTab(homePage, "HomePage");
    mainWidget->addTab(dictPage, "DictPage");
    mainWidget->tabBar()->hide();
    mainWidget->setCurrentIndex(1);

    this->titleBar()->setCustomWidget(toolbar, Qt::AlignVCenter, false);
    this->setCentralWidget(mainWidget);

    setBorderColor("#404244");

    connect(toolbar, SIGNAL(searchWord(QString)), this, SLOT(searchWord(QString)));
}

MainWindow::~MainWindow()
{

}

void MainWindow::searchWord(QString word)
{
    if (word.isEmpty())
    {
        mainWidget->setCurrentIndex(1);

        return;
    }

    mainWidget->setCurrentIndex(2);
    dictPage->queryWord(word);
}
