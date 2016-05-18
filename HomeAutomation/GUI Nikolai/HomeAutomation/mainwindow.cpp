#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_opdaterStatus_clicked()
{
    if(registryPtr != NULL) {
        registryPtr->updateStates([&](uchar ID) { return commPtr->getUnitStatus(ID); });
        /*tablePtr->setRowCount(registryPtr->getRegistrySize());
        vector<unit>::iterator it;
        for(it = registryPtr->begin(); it != registryPtr->end(); ++it){
            int c = +((*it).getUnitID());
            QString myString = to_QString(c);
            cout << c << endl;
            tablePtr->setItem(0,0, new QTableWidgetItem(myString));
        }*/



       if(tablePtr != NULL) {
            tablePtr->setRowCount(registryPtr->getRegistrySize());
            int rowCount = 0;
            vector<unit>::iterator iter;
            //QTableWidgetItem* item = new QTableWidgetItem;
            //item->setData(Qt::DisplayRole, 2);
            //tablePtr->setItem(0, 1, item);
            for(iter = registryPtr->begin(); iter != registryPtr->end(); ++iter) {
                QString inf = QString::number(+((*iter).getUnitID()));
                tablePtr->setItem( rowCount, 0, new QTableWidgetItem( inf ) );
                inf = QString::number(+((*iter).getRoomID()));
                tablePtr->setItem( rowCount, 1, new QTableWidgetItem( inf ) );
                if(+((*iter).getStatus()))
                    inf = "Tændt";
                else
                    inf = "Slukket";2-+
                tablePtr->setItem( rowCount, 2, new QTableWidgetItem( inf ) );
                rowCount += 1;
            }
        }
    }
}
