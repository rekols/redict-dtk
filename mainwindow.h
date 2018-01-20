#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <DMainWindow>
#include <QStackedLayout>
#include "toolbar.h"
#include "homepage.h"

DWIDGET_USE_NAMESPACE

class MainWindow : public DMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QWidget *m_widget;
    QStackedLayout *m_layout;
    ToolBar *m_toolBar;
    HomePage *m_homePage;
};

#endif // MAINWINDOW_H
