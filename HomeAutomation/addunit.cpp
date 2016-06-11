#include "addunit.h"
#include "ui_addunit.h"
#include <QInputDialog>
#include <QString>
//========================================================================
// FILENAME : <addUnit.h>
// CREATED : <20/05-2016>
// AUTHOR : <Anders Brondbjerg Knudsen>
// DESCR. : <Header filen for addUnit>
//
//------------------------------------------------------------------------
//
// REV. DATE/AUTHOR CHANGE DESCRIPTION
// 1.0 <20-05/2016/Anders Brondbjerg Knudsen> <Oprettelse af addUnit>
//========================================================================

//=============================================================
// METHOD : Explicit Constructor
// DESCR. : 
//=============================================================



AddUnit::AddUnit(QStackedWidget *parent, UnitRegister &regRef, CommInterface &comRef) :
    QWidget(parent),
    ui(new Ui::AddUnit)
{
    ui->setupUi(this);
    parentPtr = parent;
    setRegistryPtr(regRef);
    setCommPtr(comRef);
    this->setAccessibleName("Add Unit");


    //Blank SpinBox_2
    int blank = ui->spinBox_2->value();

    QString text1=" ";

    if(blank==0)
    {
      ui->spinBox_2->setSpecialValueText(text1);
    }


}

//=============================================================
// METHOD : Deconstructor
// DESCR. : 
//=============================================================



AddUnit::~AddUnit()
{
    delete ui;
}

//=============================================================
// METHOD : on_AddUnit_2_clicked
// DESCR. : Funktionen tilføjer enhed til unitRegister
//=============================================================




void AddUnit::on_AddUnit_2_clicked()
{
    //ID value fra SpinBox 1
     int unitID=ui->spinBox->value();

    //roomValue fra spinBox 2
     int roomID = ui->spinBox_2->value();
     cout << "add:unit: tilføj enhed : Room ID: " << roomID << endl;

     QMessageBox msgBox;
     msgBox.setWindowTitle("Udført funktion");
     msgBox.addButton(QMessageBox::Ok);

     if(getRegistryPtr()->storeUnit(Unit(unitID,roomID,0,0)) == true)
     {
         getCommPtr()->sendUnit(unitID, roomID);
         msgBox.setText("Tilføjelse af enheden succesfuld");
     }
     else
         msgBox.setText("Tilføjelse af enheden fejlede");
     if(msgBox.exec()==QMessageBox::Ok)
     getParentPtr()->setCurrentIndex(0);
}

//=============================================================
// METHOD : on_Cancel_clicked
// DESCR. : Funktionen afbryder tilføjelse af enheden 
//=============================================================



void AddUnit::on_Cancel_clicked()
{
     getParentPtr()->setCurrentIndex(0);
}
