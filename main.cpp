#include "main_window.h"
#include <DApplication>
#include <DWidgetUtil>

DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{
    //qputenv("QT_SCALE_FACTOR", "1.35");

    DApplication::loadDXcbPlugin();
    DApplication a(argc, argv);
    a.loadTranslator();
    a.setTheme("dark");

    MainWindow w;
    w.setFixedSize(520, 400);
    a.setWindowIcon(QIcon(":/resources/logo.svg"));
    w.show();

    Dtk::Widget::moveToCenter(&w);

    return a.exec();
}
