#include "main_window.h"
#include <DApplication>
#include <QDesktopWidget>

DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{
    DApplication::loadDXcbPlugin();

    DApplication a(argc, argv);

    const char *descriptionText = QT_TRANSLATE_NOOP("MainWindow", "Rekols词典是一款简单易用的词典");
    const QString acknowledgementLink = "https://github.com/rekols";

    if (a.setSingleInstance("rekols-dict"))
    {
        a.setApplicationVersion("0.3");

        a.setProductIcon(QPixmap::fromImage(QImage(":/resources/logo.svg")));
        a.setApplicationDescription(DApplication::translate("MainWindow", descriptionText) + "\n");
        a.setApplicationAcknowledgementPage(acknowledgementLink);
        a.loadTranslator();

        a.setTheme("dark");
        a.setWindowIcon(QIcon(":/resources/logo.svg"));

        MainWindow w;
        w.setFixedSize(550, 420);
        w.show();

        w.move((QApplication::desktop()->width() - w.width()) / 2, (QApplication::desktop()->height() - w.height()) / 2);
        
        return a.exec();
    }

    return 0;
}
