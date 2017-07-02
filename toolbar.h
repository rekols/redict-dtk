#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QWidget>
#include <QHBoxLayout>
#include <dimagebutton.h>

DWIDGET_USE_NAMESPACE

class ToolBar : public QWidget
{
    Q_OBJECT

public:
    ToolBar(QWidget *parent = 0);
    ~ToolBar();

    void showReturn();
    void showIcon();

    DImageButton *returnButton;

private:
    QHBoxLayout *layout;
    QLabel *iconLabel;
    QLabel *title;
};
#endif // TOOLBAR_H
