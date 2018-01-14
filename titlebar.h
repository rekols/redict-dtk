#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLineEdit>

class Titlebar : public QWidget
{
    Q_OBJECT

public:
    explicit Titlebar(QWidget *parent = nullptr);

signals:
    void textChanged(const QString &text);

private:
    QHBoxLayout *m_layout;
    QLineEdit *m_edit;
};

#endif // TITLEBAR_H
