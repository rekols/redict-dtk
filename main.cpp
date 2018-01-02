#include "main_window.h"
#include <DApplication>
#include <DWidgetUtil>

DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{
    DApplication::loadDXcbPlugin();
    DApplication a(argc, argv);

    if (a.setSingleInstance("redict")) {
        a.setAttribute(Qt::AA_UseHighDpiPixmaps);
        a.loadTranslator();
        a.setTheme("dark");
        a.setApplicationVersion("1.0");
        a.setProductIcon(QIcon(":/resources/logo.svg"));
        a.setApplicationDescription("Rekols Dictionary");

        MainWindow w;
        w.setFixedSize(520, 400);
        a.setWindowIcon(QIcon(":/resources/logo.svg"));
        w.show();

        Dtk::Widget::moveToCenter(&w);    

        return a.exec();
    }

    return 0;
}
