#ifndef SETTTINGS_H
#define SETTTINGS_H

#include <QObject>
#include <QSettings>

class Settings : public QObject
{
    Q_OBJECT

public:
    Settings(QObject *parent = 0);

    QSettings *settings;
    QString configPath();
};

#endif // SETTTINGS_H
