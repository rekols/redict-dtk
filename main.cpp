#include "main_window.h"
#include <DApplication>
#include <dutility.h>
#include <QFont>

DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{
    DApplication::loadDXcbPlugin();

    DApplication a(argc, argv);

    if (a.setSingleInstance("engine-dict"))
    {
        a.setTheme("dark");

        MainWindow w;
        w.setFixedSize(660, 500);
        w.show();

        DUtility::moveToCenter(&w);

        return a.exec();
    }

    return 0;
}
