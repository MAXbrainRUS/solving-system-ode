#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QTextCodec *defaultCodec = QTextCodec::codecForName("UTF-8"); //кодировка моих исходников - UTF-8
    QTextCodec *defaultLocaleCodec = defaultCodec;//позже может быть переопределено...
    QTextCodec::setCodecForTr(defaultCodec);
    QTextCodec::setCodecForCStrings(defaultCodec);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
