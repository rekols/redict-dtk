#include "main_window.h"
#include <DTitlebar>
#include <QTabBar>
#include "home_page.h"

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

    connect(homePage, SIGNAL(searchWord(QString)), this, SLOT(searchWord(QString)));

    connect(dictPage->returnButton, &DLinkButton::clicked, this, [=]{
        mainWidget->setCurrentIndex(1);
    });
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
