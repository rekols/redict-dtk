#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <DMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include "toolbar.h"
#include "loading_page.h"
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
    QSystemTrayIcon* trayIcon;
    QMenu *trayMenu;
    QAction *showAction;
    QAction *quitAction;

    QTabWidget *mainWidget;
    ToolBar *toolbar;
    LoadingPage *loadingPage;
    HomePage *homePage;
    DictPage *dictPage;

private slots:
    void searchWord(QString word);
};

#endif // MAIN_WINDOW_H
