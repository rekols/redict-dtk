#include "utils.h"
#include <QFile>
#include <QTextStream>

namespace Utils
{
    QString getQssFileContent(const QString &file)
    {
        QFile f(file);
        f.open(QFile::ReadOnly);

        return f.readAll();
    }
}
