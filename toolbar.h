#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QWidget>
#include <QHBoxLayout>
#include <dimagebutton.h>
#include <QLineEdit>

DWIDGET_USE_NAMESPACE

class ToolBar : public QWidget
{
    Q_OBJECT

public:
    ToolBar(QWidget *parent = 0);
    ~ToolBar();

    void showReturn();
    void showIcon();

    QLineEdit *search;
    DImageButton *returnButton;

private:
    QHBoxLayout *layout;
    QLabel *iconLabel;
    QLabel *title;
};
#endif // TOOLBAR_H
