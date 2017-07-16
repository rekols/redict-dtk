#ifndef LOADPAGE_H
#define LOADPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <dpicturesequenceview.h>

DWIDGET_USE_NAMESPACE

class LoadPage : public QWidget
{
    Q_OBJECT

public:
    LoadPage(QWidget *parent = 0);

    DPictureSequenceView *view;

private:
    QVBoxLayout *layout;
    QLabel *label;
};

#endif // LOADPAGE_H
