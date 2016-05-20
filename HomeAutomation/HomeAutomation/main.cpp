#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    UnitRegister uR;
    CommInterface cI;
    MainWindow w(uR, cI, 0);
    w.setRegistryPtr(uR);
    w.setCommPtr(cI);
    w.show();

    return a.exec();
}
