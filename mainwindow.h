#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <DMainWindow>
#include <QStackedLayout>
#include "toolbar.h"
#include "homepage.h"
#include "transpage.h"

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
    TransPage *m_transPage;
};

#endif // MAINWINDOW_H
