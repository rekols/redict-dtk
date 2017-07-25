#include "main_window.h"
#include <DTitlebar>
#include <QApplication>
#include <QClipboard>
#include <QDesktopWidget>
#include <dthememanager.h>
#include "utils.h"

MainWindow::MainWindow(QWidget *parent)
    : DMainWindow(parent)
{
    config = new Settings();
    mainWidget = new QWidget();
    layout = new QStackedLayout;
    menu = new QMenu(this);
    themeAction = new QAction("Switch Theme", this);
    toolbar = new TabBar();
    homePage = new HomePage();
    dictPage = new DictPage();
    trPage = new TranslatorPage();
    clickBox = new ClickBox();
    floatBox = new FloatBox();

    layout->addWidget(homePage);
    layout->addWidget(dictPage);
    layout->addWidget(trPage);
    layout->setCurrentIndex(1);

    mainWidget->setLayout(layout);

    menu->addAction(themeAction);

    this->titleBar()->setCustomWidget(toolbar, Qt::AlignVCenter, false);
    this->titleBar()->setWindowFlags(Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);
    this->titleBar()->setMenu(menu);
    this->setCentralWidget(mainWidget);

    connect(themeAction, &QAction::triggered, this, [=]{
        if (config->settings->value("theme").toString() == "light") {
            config->settings->setValue("theme", "dark");
            initUI();
        }else {
            config->settings->setValue("theme", "light");
            initUI();
        }
    });
    connect(toolbar, SIGNAL(switchTab(int)), this, SLOT(switchTab(int)));

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

    initUI();
}

MainWindow::~MainWindow()
{
    clickBox->deleteLater();
    floatBox->deleteLater();
}

void MainWindow::initUI()
{
    if (config->settings->value("theme").toString() == "light") {
        setBorderColor("#dddddd");

        DThemeManager::instance()->setTheme("light");
        qApp->setStyleSheet(Utils::getQssFileContent(":/image/light.qss"));

        config->settings->setValue("theme", "light");
        toolbar->changeTheme("light");
        dictPage->changeTheme("light");
    }else {
        setBorderColor("#5D5D5D");

        DThemeManager::instance()->setTheme("dark");
        qApp->setStyleSheet(Utils::getQssFileContent(":/image/dark.qss"));

        config->settings->setValue("theme", "dark");
        toolbar->changeTheme("dark");
        dictPage->changeTheme("dark");
    }
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
