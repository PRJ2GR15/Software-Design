#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QSharedMemory mem("someKey");
    if(!mem.create(1))
    {
       QMessageBox::critical(0,"Instance detected!","Application is already running!\nApplication terminating...","Ok");
       exit(0);
    }
    QApplication a(argc, argv);
    CommInterface cI;
    //Setup af com port
    cI.openComPort(3, 57600, 8, PARITY_EVEN, 1);
    UnitRegister uR;
    cI.setRegPtr(uR);
    MainWindow w(uR, cI, 0);
    w.setRegistryPtr(uR);
    w.setCommPtr(cI);
    w.show();
    //cI.PCConnected();

    return a.exec();
}
