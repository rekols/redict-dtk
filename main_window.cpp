#include "main_window.h"
#include <DTitlebar>
#include <QApplication>
#include <QClipboard>
#include <QDesktopWidget>
#include <dthememanager.h>
#include "utils.h"
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : DMainWindow(parent)
{
    config = new Settings();
    mainWidget = new QWidget();
    layout = new QStackedLayout;
    menu = new QMenu(this);
    themeAction = new QAction("切换主题", this);
    toolbar = new TabBar();
    homePage = new HomePage();
    dictPage = new DictPage();
    trPage = new TranslatorPage();

    layout->addWidget(homePage);
    layout->addWidget(dictPage);
    layout->addWidget(trPage);
    layout->setCurrentIndex(1);

    mainWidget->setLayout(layout);

    menu->addAction(themeAction);

    this->titlebar()->setSeparatorVisible(true);
    this->titlebar()->setCustomWidget(toolbar, Qt::AlignVCenter, false);
    this->titlebar()->setWindowFlags(Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);
    this->titlebar()->setMenu(menu);
    this->setCentralWidget(mainWidget);

    connect(toolbar, SIGNAL(switchTab(int)), this, SLOT(switchTab(int)));

    connect(themeAction, &QAction::triggered, this, [=]{
        if (config->settings->value("theme").toString() == "light") {
            config->settings->setValue("theme", "dark");
            initUI();
        }else {
            config->settings->setValue("theme", "light");
            initUI();
        }
    });

    initUI();
}

MainWindow::~MainWindow()
{

}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setPen(Qt::NoPen);

    if (config->settings->value("theme").toString() == "light")
        painter.setBrush(QColor("#FFFFFF"));
    else
        painter.setBrush(QColor("#292B2E"));

    painter.drawRect(rect());
}

void MainWindow::initUI()
{
    if (config->settings->value("theme").toString() == "light") {
        setBorderColor("#dddddd");

        DThemeManager::instance()->setTheme("light");
        qApp->setStyleSheet(Utils::getQssFileContent(":/resources/light.qss"));

        config->settings->setValue("theme", "light");
        toolbar->changeTheme("light");
        dictPage->changeTheme("light");
    }else {
        setBorderColor("#5D5D5D");

        DThemeManager::instance()->setTheme("dark");
        qApp->setStyleSheet(Utils::getQssFileContent(":/resources/dark.qss"));

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
