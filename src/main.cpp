#include <QtGui/QApplication>
#include <QTranslator>
#include "widget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString locale = QLocale::system().name().section('_', 0, 0);
    if (locale != "fr")
      locale = "en";


    QTranslator translator;
    translator.load(QString(":ts/srm_") + locale);
    a.installTranslator(&translator);
    Widget w;
    w.show();
    return a.exec();
}
