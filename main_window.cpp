#include "main_window.h"
#include <DTitlebar>
#include "home_page.h"
#include <QTabBar>

MainWindow::MainWindow(QWidget *parent)
    : DMainWindow(parent)
{
    trayIcon = new QSystemTrayIcon(this);
    trayMenu = new QMenu();
    showAction = new QAction("显示", this);
    quitAction = new QAction("退出", this);
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
    this->titleBar()->setWindowFlags(Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);
    this->setCentralWidget(mainWidget);

    connect(toolbar, SIGNAL(searchWord(QString)), this, SLOT(searchWord(QString)));

    connect(dictPage->returnButton, &DLinkButton::clicked, this, [=]{
        toolbar->searchEdit->setText("");
        toolbar->searchEdit->setFocus();

        mainWidget->setCurrentIndex(1);
    });

    trayMenu->addAction(showAction);
    trayMenu->addAction(quitAction);

    trayIcon->setIcon(QIcon(":/image/logo.svg"));
    trayIcon->setContextMenu(trayMenu);
    trayIcon->show();

    connect(showAction, &QAction::triggered, this, [=]{
        this->show();
    });
    connect(quitAction, &QAction::triggered, this, [=]{
        this->close();
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
