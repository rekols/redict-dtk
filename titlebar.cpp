#include "titlebar.h"
#include <QSvgWidget>

Titlebar::Titlebar(QWidget *parent)
    : QWidget(parent),
      m_layout(new QHBoxLayout(this)),
      m_edit(new QLineEdit)
{
    QSvgWidget *iconWidget = new QSvgWidget(":/images/redict.svg");
    iconWidget->setFixedSize(22, 22);

    m_edit->setFixedWidth(360);

    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->addWidget(iconWidget);
    m_layout->addStretch();
    m_layout->addWidget(m_edit);
    m_layout->addSpacing(45);

    m_edit->setStyleSheet("QLineEdit {"
                          "border-radius: 4px;"
                          "border: 1px solid rgba(44, 167, 158, 100);"
                          "}");

    connect(m_edit, SIGNAL(textChanged(QString)), this, SIGNAL(textChanged(QString)));
}
