#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QWidget>
#include <QHBoxLayout>
#include <QTabBar>

class ToolBar : public QWidget
{
    Q_OBJECT

public:
    ToolBar(QWidget *parent = nullptr);

private:
    QHBoxLayout *m_layout;
    QTabBar *m_tabbar;
};

#endif // TOOLBAR_H
