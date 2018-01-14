#ifndef SLIDEBAR_H
#define SLIDEBAR_H

#include <QWidget>

class SlideBar : public QWidget
{
    Q_OBJECT

public:
    explicit SlideBar(QWidget *parent = nullptr);

signals:
    void currentIndexChanged(const int &index);

protected:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

private:
    int m_rowHeight;
    int m_currentIndex;
    QStringList m_listItems;
};

#endif // SLIDEBAR_H
