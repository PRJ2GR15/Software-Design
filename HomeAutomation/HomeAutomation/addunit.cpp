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
}

AddUnit::~AddUnit()
{
    delete ui;
}

void AddUnit::on_pushButton_clicked()
{

  int xvalue=ui->spinBox->value();
  Unit tempUnit(xvalue,1,2,1);

  getRegistryPtr()->storeUnit(tempUnit); //Filen findes ikke ?
}


void AddUnit::on_pushButton_3_clicked()
{
    QString N = QInputDialog::getText(this,"Tilføj nyt rum","Tilføj rum");
    ui->comboBox->addItem(N);

}

void AddUnit::on_pushButton_2_clicked()
{
    getParentPtr()->setCurrentIndex(0);
}
