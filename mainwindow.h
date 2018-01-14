#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <DMainWindow>
#include <QHBoxLayout>
#include <QStackedLayout>
#include "titlebar.h"
#include "slidebar.h"
#include "homepage.h"
#include "transpage.h"

DWIDGET_USE_NAMESPACE

class MainWindow : public DMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void currentIndexChanged(const int &index);

private:
    QWidget *m_centralWidget;
    QHBoxLayout *m_centralLayout;
    QStackedLayout *m_stackedLayout;
    Titlebar *m_titlebar;
    SlideBar *m_slideBar;
    HomePage *m_homePage;
    TransPage *m_transPage;
};

#endif // MAINWINDOW_H
