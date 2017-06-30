#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QWidget>
#include <QHBoxLayout>
#include <QTimer>
#include <dsearchedit.h>
#include <dlineedit.h>

DWIDGET_USE_NAMESPACE

class ToolBar : public QWidget
{
    Q_OBJECT

public:
    ToolBar(QWidget *parent = 0);
    ~ToolBar();

    DLineEdit *searchEdit;

private:
    void keyPressEvent(QKeyEvent *event);

signals:
    void searchWord(QString word);
};

#endif // TOOLBAR_H
