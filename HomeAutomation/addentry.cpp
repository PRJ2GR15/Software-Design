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
    setTablePtr(this->findChild<QTableWidget*>("entry_Table"));
    populateTable();
}

AddEntry::~AddEntry()
{
    delete ui;
}

void AddEntry::getUnit(int id)
{
    unitID=id;
}

void AddEntry::setTablePtr(QTableWidget* tableRef) {
    if(tableRef != NULL) {
        tablePtr = tableRef;
        //Sørger for at man ikke kan redigere i vores table.
        tablePtr->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tablePtr->setSelectionBehavior(QAbstractItemView::SelectRows);
        tablePtr->setSelectionMode(QAbstractItemView::SingleSelection);
    }
    else
        cerr << "Couldn't register table address" << endl;
}

void AddEntry::populateTable()
{
    int rows=2;//Da starttid og sluttids udfyldes på en linje, men hentes ind som to.
    int rowCount =0;
    QString inf;
    if(getRegistryPtr() != NULL)
        if(tablePtr != NULL)
        {
            vector<Unit>::iterator iter;

            for(iter = getRegistryPtr()->begin(); iter != getRegistryPtr()->end(); ++iter)
            {
                if(iter->getUnitID()==unitID)
                {
                    int entries = iter->getEntryID();
                    tablePtr->setRowCount(iter->getSize()/rows);

                    for(int i = 0 ; i<entries ; i++)
                    {
                        int day = iter->compareEntryID(i);

                        if(day==0)
                        {
                        inf="Mandag";
                        }
                        else if(day==1)
                        {
                        inf="Tirsdag";
                        }
                        else if(day==2)
                        {
                        inf="Onsdag";
                        }
                        else if(day==3)
                        {
                        inf="Torsdag";
                        }
                        else if(day==4)
                        {
                        inf="Fredag";
                        }
                        else if(day==5)
                        {
                        inf="Lørdag";
                        }
                        else
                            inf="Søndag";

                        tablePtr->setItem(rowCount,0,new QTableWidgetItem(inf) );
                         rowCount+=1;
                    }



                   // tablePtr->setItem(rowCount,0,new QTableWidgetItem(inf) );


                    rowCount+=1;

                }
            }
        }
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
             if(iter->getUnitID()==unitID)
             {

                 if(iter->storeEntry(valgteDag,Entry(iter->getEntryID(),setHour,setMin,1))==true) //Tilføjer start tidsplan
                 {

                    iter->storeEntry(valgteDag,Entry(iter->getEntryID(),endHour,endMin,0));//Tilføjer slut tidsplan

                         msgBox.setText("Tilføjelse af enheden succesfuld");
                         iter->countEntryID();
                 }
                 else
                        msgBox.setText("Tilføjelse af enheden fejlede");
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
