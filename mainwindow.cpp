#include "mainwindow.h"
#include "dtitlebar.h"

MainWindow::MainWindow(QWidget *parent)
    : DMainWindow(parent),
      m_centralWidget(new QWidget),
      m_centralLayout(new QHBoxLayout(m_centralWidget)),
      m_stackedLayout(new QStackedLayout),
      m_titlebar(new Titlebar),
      m_slideBar(new SlideBar),
      m_homePage(new HomePage),
      m_transPage(new TransPage)
{
    if (titlebar()) {
        titlebar()->setFixedHeight(45);
        titlebar()->setSeparatorVisible(true);
        titlebar()->setCustomWidget(m_titlebar, Qt::AlignVCenter, false);
    }

    m_stackedLayout->addWidget(m_homePage);
    m_stackedLayout->addWidget(m_transPage);

    m_centralLayout->setContentsMargins(0, 0, 0, 0);
    m_centralLayout->setSpacing(0);
    m_centralLayout->addWidget(m_slideBar);
    m_centralLayout->addLayout(m_stackedLayout);

    setFixedSize(640, 450);
    setWindowIcon(QIcon(":/images/redict.svg"));
    setCentralWidget(m_centralWidget);
    setShadowOffset(QPoint(0, 0));

    connect(m_titlebar, &Titlebar::textChanged, m_homePage, &HomePage::queryWord);
    connect(m_slideBar, &SlideBar::currentIndexChanged, this, &MainWindow::currentIndexChanged);
}

MainWindow::~MainWindow()
{

}

void MainWindow::currentIndexChanged(const int &index)
{
    m_stackedLayout->setCurrentIndex(index);
}
