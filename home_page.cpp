#include "home_page.h"

HomePage::HomePage(QWidget *parent)
    : QWidget(parent)
{
    layout = new QStackedLayout(this);
    loadPage = new LoadPage;
    dataPage = new DataPage;

    layout->addWidget(loadPage);
    layout->addWidget(dataPage);

    layout->setCurrentIndex(0);

    connect(dataPage, &DataPage::loadImageFinished, this, [=]{
        layout->setCurrentIndex(1);

        loadPage->view->stop();
    });
}

HomePage::~HomePage()
{

}
