#include "addentry.h"
#include "ui_addentry.h"
#include <QInputDialog>

AddEntry::AddEntry(QStackedWidget *parent, UnitRegister& regRef, CommInterface& comRef) :
    QWidget(parent),
    ui(new Ui::AddEntry)
{
    ui->setupUi(this);
    this->setAccessibleName("Add Entry");

    parentPtr = parent;
    setRegistryPtr(regRef);
    setCommPtr(comRef);
}

AddEntry::~AddEntry()
{
    delete ui;
}

void AddEntry::on_pushButton_clicked()
{

    QString date = ui->comboBox->currentText();
    int valgteDag=0;
    if(date=="Mandag")
        valgteDag=0;
    else if(date=="Tirsdag")
        valgteDag=1;
    else if(date=="Onsdag")
        valgteDag=2;
    else if(date=="Torsdag")
        valgteDag=3;
    else if(date=="Fredag")
        valgteDag=4;
    else if(date=="Lørdag")
        valgteDag=5;
    else
        valgteDag=6;

    //Få start tid
    int setHour = ui->StartTime->time().hour();
    int setMin = ui->StartTime->time().minute();
    //Få slutid
    int endHour = ui->EndTime->time().hour();
    int endMin = ui->EndTime->time().minute();



     vector<Unit>::iterator iter;
     QMessageBox msgBox;
     msgBox.setWindowTitle("Udført funktion");
     msgBox.addButton(QMessageBox::Ok);




     if((setHour<endHour)||((setHour==endHour)& (setMin<endMin)))
    {
         for(iter = getRegistryPtr()->begin(); iter != getRegistryPtr()->end(); ++iter)
         {
             if(iter->getUnitID()==2)
             {
                 if(iter->storeEntry(valgteDag,Entry(setHour,setMin,1))==true) //Tilføjer start tidsplan
                 {
                    iter->storeEntry(valgteDag,Entry(endHour,endMin,0));//Tilføjer slut tidsplan

                         msgBox.setText("Tilføjelse af enheden succesfuld");

                 }
                 else
                        msgBox.setText("Fejl- Eksisterende tidsplan findes allerede");
            }

        }
     }

    else
      msgBox.setText("Tilføjelse af enheden fejlede");
   if(msgBox.exec()==QMessageBox::Ok)
    parentPtr->setCurrentIndex(0);
}

void AddEntry::on_pushButton_2_clicked()
{
    parentPtr->setCurrentIndex(0);
}
