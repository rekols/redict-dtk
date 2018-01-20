#ifndef UTILS_H
#define UTILS_H

#include <QObject>

class Utils : public QObject
{
    Q_OBJECT

public:
    Utils(QObject *parent = nullptr);

    static QString getQssContent(const QString &fileName);
};

#endif // UTILS_H
