#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    EnhedsRegister e;
    CommInterface c;
    w.setRegistryPtr(e);
    w.setCommPtr(c);
    w.setTablePtr(w.findChild<QTableWidget*>("myTable"));

    w.show();

    return a.exec();
}
