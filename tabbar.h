#ifndef TABBAR_H
#define TABBAR_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QMouseEvent>
#include <QFontMetrics>

class TabBar : public QWidget
{
    Q_OBJECT

public:
    TabBar(QWidget *parent = 0);

    void changeTheme(const QString &theme);

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);

private:
    QHBoxLayout *layout;
    QLabel *iconLabel;

    QList<QString> tabNames;
    QList<int> tabNameWidths;
    QFontMetrics *fontMetrics;
    int currentTabIndex;
    int tabNameSize;

    QString tabNameColor;

signals:
    void switchTab(int index);
};

#endif // TABBAR_H
