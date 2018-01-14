#include "mainwindow.h"
#include <DApplication>
#include <DWidgetUtil>

DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{
    DApplication::loadDXcbPlugin();
    DApplication a(argc, argv);


    if (a.setSingleInstance("redict")) {
        a.setAttribute(Qt::AA_UseHighDpiPixmaps);
        a.setOrganizationName("deepin");
        a.setApplicationVersion("0.1");
        a.setProductIcon(QIcon(":/images/redict.svg"));
        a.setProductName(DApplication::translate("Main", "Rekols Dictionary"));
        a.setApplicationDescription(DApplication::translate("Main", "ReDict is a simple dictionary for deepin."));

        MainWindow w;
        w.show();

        Dtk::Widget::moveToCenter(&w);

        return a.exec();
    }

    return 0;
}
