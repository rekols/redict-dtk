#include "utils.h"
#include <QFile>

Utils::Utils(QObject *parent)
    : QObject(parent)
{

}

QString Utils::getQssContent(const QString &fileName)
{
    QFile file(fileName);
    QString contents;

    file.open(QIODevice::ReadOnly);
    contents = file.readAll();
    file.close();

    return contents;
}
