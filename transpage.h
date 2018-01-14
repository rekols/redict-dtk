#ifndef TRANSPAGE_H
#define TRANSPAGE_H

#include <QWidget>
#include <QVBoxLayout>

class TransPage : public QWidget
{
    Q_OBJECT
    
public:
    TransPage(QWidget *parent = nullptr);
    ~TransPage(); 
};

#endif
