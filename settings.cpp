#include "settings.h"
#include <QApplication>
#include <QDir>
#include <QStandardPaths>

Settings::Settings(QObject *parent)
    : QObject(parent)
{
    settings = new QSettings(QDir(configPath()).filePath("config.conf") , QSettings::IniFormat);

    if (settings->value("theme").toString().isEmpty()) {
        settings->setValue("theme", "light");
    }
}

QString Settings::configPath()
{
    return QDir(QDir(QStandardPaths::standardLocations(QStandardPaths::ConfigLocation).first()).filePath(qApp->organizationName())).filePath(qApp->applicationName());
}
