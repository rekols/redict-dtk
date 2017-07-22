#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <DMainWindow>
#include <QStackedLayout>
#include "tabbar.h"
#include "home_page.h"
#include "dict_page.h"
#include "translator_page.h"
#include "event_monitor.h"
#include "click_box.h"
#include "float_box.h"

DWIDGET_USE_NAMESPACE

class MainWindow : public DMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QWidget *mainWidget;
    QStackedLayout *layout;
    TabBar *toolbar;
    HomePage *homePage;
    DictPage *dictPage;
    TranslatorPage *trPage;
    EventMonitor eventMonitor;

    ClickBox *clickBox;
    FloatBox *floatBox;

protected:
    void closeEvent(QCloseEvent *);

private slots:
    void switchTab(int index);
};

#endif // MAIN_WINDOW_H
