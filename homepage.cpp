#include "homepage.h"

HomePage::HomePage(QWidget *parent)
    : QWidget(parent),
      m_layout(new QVBoxLayout(this)),
      m_edit(new QLineEdit),
      m_stackedWidget(new QStackedWidget),
      m_infoPage(new InfoPage),
      m_dictPage(new DictPage)
{
    m_edit->setObjectName("SearchEdit");
    m_edit->setFixedHeight(32);

    m_layout->setContentsMargins(20, 10, 20, 0);
    m_layout->addWidget(m_edit);
    m_layout->addSpacing(5);
    m_layout->addWidget(m_stackedWidget);

    m_stackedWidget->addWidget(m_infoPage);
    m_stackedWidget->addWidget(m_dictPage);

    connect(m_edit, &QLineEdit::textChanged, this, &HomePage::textChanged);
}

void HomePage::textChanged(const QString &text)
{
    if (text.isEmpty()) {
        m_stackedWidget->setCurrentIndex(0);
    } else {
        m_dictPage->queryWord(text);
        m_stackedWidget->setCurrentIndex(1);
    }
}
