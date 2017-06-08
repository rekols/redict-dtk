#ifndef INDICATORTAB_H
#define INDICATORTAB_H

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

#include "dloadingindicator.h"

DWIDGET_USE_NAMESPACE

class LoadingPage : public QLabel
{
    Q_OBJECT

public:
    explicit LoadingPage(QWidget *parent = 0);
};

#endif // INDICATORTAB_H
