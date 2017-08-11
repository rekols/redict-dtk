#include "main_window.h"
#include <dtitlebar.h>
#include <dthememanager.h>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : DMainWindow(parent)
{
    widget = new QWidget();
    layout = new QStackedLayout();
    toolbar = new ToolBar();
    loadPage = new LoadPage();
    homePage = new HomePage();
    dictPage = new DictPage();
    config = new Settings();
    menu = new QMenu();

    layout->addWidget(loadPage);
    layout->addWidget(homePage);
    layout->addWidget(dictPage);

    widget->setLayout(layout);

    titlebar()->setWindowFlags(titlebar()->windowFlags() & ~Qt::WindowMaximizeButtonHint);
    titlebar()->setCustomWidget(toolbar, Qt::AlignHCenter, false);
    titlebar()->setSeparatorVisible(true);
    titlebar()->setMenu(menu);

    QAction *themeAction = new QAction("切换主题", this);
    menu->addAction(themeAction);

    connect(themeAction, &QAction::triggered, this, [=]{
        if (config->settings->value("theme").toString() == "light") {
            config->settings->setValue("theme", "dark");
            initUI();
        }else {
            config->settings->setValue("theme", "light");
            initUI();
        }
    });

    connect(homePage, &HomePage::loadImageFinished, this, [=]{
        if (layout->currentIndex() == 2) {
            return;
        }

        layout->setCurrentIndex(1);
    });

    connect(toolbar->edit, &QLineEdit::textChanged, this, [=]{
        if (toolbar->edit->text().isEmpty()) {
            layout->setCurrentIndex(1);
            return;
        }

        dictPage->api->queryWord(toolbar->edit->text());
        layout->setCurrentIndex(2);
    });

    connect(toolbar->edit, &QLineEdit::returnPressed, this, [=]{
        if (toolbar->edit->text().isEmpty()) {
            layout->setCurrentIndex(1);
            return;
        }

        dictPage->api->queryWord(toolbar->edit->text());
        layout->setCurrentIndex(2);
    });

    setCentralWidget(widget);

    initUI();
}

MainWindow::~MainWindow()
{

}

void MainWindow::initUI()
{
    if (config->settings->value("theme").toString() == "light") {
        setBorderColor("#dddddd");

        DThemeManager::instance()->setTheme("light");

        config->settings->setValue("theme", "light");
        dictPage->changeTheme("light");
    }else {
        setBorderColor("#5D5D5D");

        DThemeManager::instance()->setTheme("dark");

        config->settings->setValue("theme", "dark");
        dictPage->changeTheme("dark");
    }
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
