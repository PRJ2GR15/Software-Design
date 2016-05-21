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

AddUnit::AddUnit(QStackedWidget *parent, UnitRegister &regRef, CommInterface &comRef) :
    QWidget(parent),
    ui(new Ui::AddUnit)
{
    ui->setupUi(this);
    parentPtr = parent;
    setRegistryPtr(regRef);
    setCommPtr(comRef);



    //Blank SpinBox_2
    int blank = ui->spinBox_2->value();

    QString text1=" ";

    if(blank==0)
    {
      ui->spinBox_2->setSpecialValueText(text1);
    }


}

AddUnit::~AddUnit()
{
    delete ui;
}

void AddUnit::on_pushButton_clicked()
{
 //ID value fra SpinBox 1
  int IDValue=ui->spinBox->value();

 //roomValue fra spinBox 2
  int roomValue = ui->spinBox_2->value();

//Temp Unit indeholdende overstående data
  Unit tempUnit(IDValue,roomValue,2,1);
  cout << tempUnit;

  QMessageBox msgBox;
  msgBox.setWindowTitle("Udført funktion");
  msgBox.addButton(QMessageBox::Ok);

  if(getRegistryPtr()->storeUnit(tempUnit)==true)
  {
      msgBox.setText("Tilføjelse af enheden succesfuld");
  }
  else
      msgBox.setText("Tilføjelse af enheden fejlede");
  if(msgBox.exec()==QMessageBox::Ok)
  getParentPtr()->setCurrentIndex(0);
}


void AddUnit::on_pushButton_2_clicked()
{
    getParentPtr()->setCurrentIndex(0);
}
