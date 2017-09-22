#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <DMainWindow>
#include <QStackedLayout>
#include "toolbar.h"
#include "load_page.h"
#include "home_page.h"
#include "dict_page.h"
#include "settings.h"

#include <QMenu>

DWIDGET_USE_NAMESPACE

class MainWindow : public DMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QWidget *widget;
    QStackedLayout *layout;
    ToolBar *toolbar;
    LoadPage *loadPage;
    HomePage *homePage;
    DictPage *dictPage;

    Settings *config;
    QMenu *menu;

    void initUI();
};

#endif // MAIN_WINDOW_H
