#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    UnitRegister uR;
    CommInterface cI;
    w.setRegistryPtr(uR);
    w.setCommPtr(cI);
    w.show();

    return a.exec();
}
