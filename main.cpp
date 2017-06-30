#include "main_window.h"
#include <DApplication>
#include <dutility.h>

DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{
    DApplication::loadDXcbPlugin();

    DApplication a(argc, argv);

    if (a.setSingleInstance("rekols-dict"))
    {
        a.setTheme("light");
        a.setWindowIcon(QIcon(":/image/logo.svg"));

        MainWindow w;
        w.setMinimumSize(550, 400);
        w.setFixedSize(550, 400);
        w.show();

        DUtility::moveToCenter(&w);

        return a.exec();
    }

    return 0;
}
