#include "toolbar.h"
#include <QSvgWidget>

ToolBar::ToolBar(QWidget *parent)
    : QWidget(parent),
      m_layout(new QHBoxLayout(this)),
      m_tabbar(new QTabBar)
{
    QSvgWidget *iconWidget = new QSvgWidget;
    iconWidget->load(QString(":/images/redict.svg"));
    iconWidget->setFixedSize(22, 22);

    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->addSpacing(5);
    m_layout->addWidget(iconWidget);
    m_layout->addSpacing(2);
    m_layout->addWidget(m_tabbar);
    m_layout->addStretch();

    m_tabbar->setFocusPolicy(Qt::NoFocus);
    m_tabbar->addTab("查词");
    m_tabbar->addTab("翻译");
    
    connect(m_tabbar, SIGNAL(currentChanged(int)), this, SIGNAL(tabBarIndexChanged(int)));
}
