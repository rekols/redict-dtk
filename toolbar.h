#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QWidget>
#include <QHBoxLayout>
#include <QTimer>
#include <dsearchedit.h>

DWIDGET_USE_NAMESPACE

class ToolBar : public QWidget
{
    Q_OBJECT

public:
    ToolBar(QWidget *parent = 0);
    ~ToolBar();

private:
    DSearchEdit *searchEdit;

    void keyPressEvent(QKeyEvent *event);

signals:
    void searchWord(QString word);
};

#endif // TOOLBAR_H
