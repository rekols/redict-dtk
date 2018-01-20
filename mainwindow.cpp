#include "mainwindow.h"
#include "dtitlebar.h"
#include "utils.h"

MainWindow::MainWindow(QWidget *parent)
    : DMainWindow(parent),
      m_widget(new QWidget),
      m_layout(new QStackedLayout(m_widget)),
      m_toolBar(new ToolBar),
      m_homePage(new HomePage)
{
    if (titlebar()) {
        titlebar()->setCustomWidget(m_toolBar, Qt::AlignVCenter, false);
        titlebar()->setSeparatorVisible(true);
    }

    m_layout->addWidget(m_homePage);

    setStyleSheet(Utils::getQssContent(":/qss/light/style.qss"));
    setFixedSize(550, 400);
    setCentralWidget(m_widget);
}

MainWindow::~MainWindow()
{

}
