#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QWidget>
#include <QLineEdit>

class ToolBar : public QWidget
{
    Q_OBJECT

public:
    ToolBar(QWidget *parent = 0);

    QLineEdit *edit;
};

#endif // TOOLBAR_H
