#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QStackedLayout>
#include "load_page.h"
#include "data_page.h"

class HomePage : public QWidget
{
    Q_OBJECT

public:
    HomePage(QWidget *parent = 0);
    ~HomePage();

private:
    QStackedLayout *layout;
    LoadPage *loadPage;
    DataPage *dataPage;

};

#endif // HOMEPAGE_H
