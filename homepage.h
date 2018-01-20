#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QStackedWidget>
#include "infopage.h"
#include "dictpage.h"

class HomePage : public QWidget
{
    Q_OBJECT

public:
    HomePage(QWidget *parent = nullptr);

private slots:
    void textChanged(const QString &text);
    
private:
    QVBoxLayout *m_layout;
    QLineEdit *m_edit;
    QStackedWidget *m_stackedWidget;
    InfoPage *m_infoPage;
    DictPage *m_dictPage;
};

#endif // HOMEPAGE_H
