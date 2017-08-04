#include "main_window.h"
#include <DApplication>
#include <DWidgetUtil>

DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{
    DApplication::loadDXcbPlugin();
    DApplication a(argc, argv);
    a.setTheme("dark");

    MainWindow w;
    w.setFixedSize(520, 420);
    a.setWindowIcon(QIcon(":/resources/logo.svg"));
    w.show();

    Dtk::Widget::moveToCenter(&w);

    return a.exec();
}
