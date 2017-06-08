#include "main_window.h"
#include <DApplication>
#include <dutility.h>

DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{
    DApplication::loadDXcbPlugin();

    DApplication a(argc, argv);

    if (a.setSingleInstance("engine-dict"))
    {
        a.setTheme("light");

        MainWindow w;
        w.setMinimumSize(660, 500);
        w.resize(660, 500);
        w.show();

        DUtility::moveToCenter(&w);

        return a.exec();
    }

    return 0;
}
