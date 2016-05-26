#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CommInterface cI;
    cI.openComPort(3, 9600, 8, 2, 1);
    UnitRegister uR;
    cI.setRegPtr(uR);
    cI.getAllUnits();
    MainWindow w(uR, cI, 0);
    w.setRegistryPtr(uR);
    w.setCommPtr(cI);
    w.show();
    //cI.PCConnected();

    return a.exec();
}
