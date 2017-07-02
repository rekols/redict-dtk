#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <DMainWindow>
#include "toolbar.h"
#include "home_page.h"
#include "dict_page.h"

DWIDGET_USE_NAMESPACE

class MainWindow : public DMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QTabWidget *mainWidget;
    ToolBar *toolbar;
    HomePage *homePage;
    DictPage *dictPage;

private slots:
    void searchWord(QString word);
};

#endif // MAIN_WINDOW_H
