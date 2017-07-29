#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <DMainWindow>
#include <QStackedLayout>
#include <QMenu>
#include "tabbar.h"
#include "home_page.h"
#include "dict_page.h"
#include "translator_page.h"
#include "event_monitor.h"
#include "click_box.h"
#include "float_box.h"
#include "settings.h"

DWIDGET_USE_NAMESPACE

class MainWindow : public DMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *);

private:
    Settings *config;
    QWidget *mainWidget;
    QStackedLayout *layout;
    QMenu *menu;
    QAction *themeAction;
    QAction *openUnderline;
    QAction *closeUnderline;
    TabBar *toolbar;
    HomePage *homePage;
    DictPage *dictPage;
    TranslatorPage *trPage;
    EventMonitor eventMonitor;

    ClickBox *clickBox;
    FloatBox *floatBox;

    void initUI();

private slots:
    void switchTab(int index);
    void openUnderLine();
    void closeUnderLine();
};

#endif // MAIN_WINDOW_H
