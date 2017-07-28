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
    openUnderline = new QAction("打开划词", this);
    closeUnderline = new QAction("关闭划词", this);
    toolbar = new TabBar();
    homePage = new HomePage();
    dictPage = new DictPage();
    trPage = new TranslatorPage();
    clickBox = new ClickBox();
    floatBox = new FloatBox();
    backgroundColor = "#FFFFFF";

    layout->addWidget(homePage);
    layout->addWidget(dictPage);
    layout->addWidget(trPage);
    layout->setCurrentIndex(1);

    mainWidget->setLayout(layout);

    menu->addAction(themeAction);
    menu->addAction(openUnderline);
    menu->addAction(closeUnderline);

    if (config->settings->value("underline").toString() == "true") {
        openUnderLine();
    }else {
        closeUnderLine();
    }

    connect(openUnderline, &QAction::triggered, this, &MainWindow::openUnderLine);
    connect(closeUnderline, &QAction::triggered, this, &MainWindow::closeUnderLine);

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

    initUI();
}

MainWindow::~MainWindow()
{
    clickBox->deleteLater();
    floatBox->deleteLater();
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(backgroundColor));
    painter.drawRect(rect());
}

void MainWindow::initUI()
{
    if (config->settings->value("theme").toString() == "light") {
        backgroundColor = "#FFFFFF";
        setBorderColor("#dddddd");

        DThemeManager::instance()->setTheme("light");
        qApp->setStyleSheet(Utils::getQssFileContent(":/image/light.qss"));

        config->settings->setValue("theme", "light");
        toolbar->changeTheme("light");
        dictPage->changeTheme("light");
    }else {
        backgroundColor = "#292B2E";
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

void MainWindow::openUnderLine()
{
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

    config->settings->setValue("underline", "true");
    openUnderline->setVisible(false);
    closeUnderline->setVisible(true);
}

void MainWindow::closeUnderLine()
{
    disconnect(qApp->clipboard(), 0, 0, 0);
    disconnect(clickBox, 0, 0, 0);
    disconnect(&eventMonitor, 0, 0, 0);

    config->settings->setValue("underline", "false");
    openUnderline->setVisible(true);
    closeUnderline->setVisible(false);
}
