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
    //cI.closeComPort();
    //TEST AF KOMMUNIKATION
    cI.openComPort(3, 9600, 8, 2, 1);
    //PC TILSLUTTET KOMMANDO
    //char cmd[5] = {0xF0, 0xF0, 0x01, 0x0F, 0x0F};
    //cI.sendCommand(cmd, 5);
    //cI.readInputBuffer();

    return a.exec();
}
