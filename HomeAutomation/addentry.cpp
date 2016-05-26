#include "addentry.h"
#include "ui_addentry.h"
#include "entry.h"
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
                    iter->printEntry();


                    tablePtr->setRowCount(iter->getSize()/rows);
                    vector< vector<Entry> > myRef = iter->getEntryRegisterRef();
                    int dayCounter = 0;
                    int rowCounter = 0;
                    map<unsigned char, int> myMap;
                    for(auto day : myRef) {
                        for(auto entry : day) {
                            switch(dayCounter) {
                            case 0:
                                inf = "Mandag";
                                break;
                            case 1:
                                inf = "Tirsdag";
                                break;
                            case 2:
                                inf = "Onsdag";
                                break;
                            case 3:
                                inf = "Torsdag";
                                break;
                            case 4:
                                inf = "Fredag";
                                break;
                            case 5:
                                inf = "Lørdag";
                                break;
                            case 6:
                                inf = "Søndag";
                                break;
                            default:
                                inf = "default";
                            }
                            if(entry.getAction()) {
                                QString tmpQString;
                                myMap[entry.EntryID()] = rowCounter;
                                tablePtr->setItem(rowCounter,0,new QTableWidgetItem(inf) );
                                if(+entry.getHour() < 10) {
                                    tmpQString = "0" + QString::number(+entry.getHour()) + ":";
                                    if(entry.getMin() < 10) {
                                        tmpQString.append("0" + QString::number(+entry.getMin() ) );
                                    }
                                    else
                                        tmpQString.append(QString::number(+entry.getMin()));
                                }
                                else {
                                    tmpQString = QString::number(+entry.getHour()) + ":";
                                    if(entry.getMin() < 10) {
                                        tmpQString.append("0" + QString::number(+entry.getMin() ) );
                                    }
                                    else
                                        tmpQString.append(QString::number(+entry.getMin()));
                                }
                                tablePtr->setItem(rowCounter,1, new QTableWidgetItem(tmpQString) );
                                rowCounter++;
                            }
                            else {
                                QString tmpQString;
                                if(+entry.getHour() < 10) {
                                    tmpQString = "0" + QString::number(+entry.getHour()) + ":";
                                    if(entry.getMin() < 10) {
                                        tmpQString.append("0" + QString::number(+entry.getMin() ) );
                                    }
                                    else
                                        tmpQString.append(QString::number(+entry.getMin()));
                                }
                                else {
                                    tmpQString = QString::number(+entry.getHour()) + ":";
                                    if(entry.getMin() < 10) {
                                        tmpQString.append("0" + QString::number(+entry.getMin() ) );
                                    }
                                    else
                                        tmpQString.append(QString::number(+entry.getMin()));
                                }
                                //int thisRow = myMap[entry.EntryID()];
                                tablePtr->setItem(myMap[entry.EntryID()],2, new QTableWidgetItem(tmpQString) );
                            }
                        }
                        dayCounter++;
                    }
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
    int startHour = ui->StartTime->time().hour();
    int startMin = ui->StartTime->time().minute();
    //Få slutid
    int endHour = ui->EndTime->time().hour();
    int endMin = ui->EndTime->time().minute();

     vector<Unit>::iterator iter;
     QMessageBox msgBox;
     msgBox.setWindowTitle("Udført funktion");
     msgBox.addButton(QMessageBox::Ok);

     if( (startHour<endHour) || ( (startHour==endHour) & (startMin<endMin) ))
    {
         for(iter = getRegistryPtr()->begin(); iter != getRegistryPtr()->end(); ++iter)
         {
             if(iter->getUnitID()==unitID)
             {
                if((iter->compareEntry(Entry(iter->getEntryID(),startHour,startMin,1),valgteDag)==false) && (iter->compareEntry(Entry(iter->getEntryID(),endHour,endMin,0),valgteDag))==false)
                {
                    //Be om at få et fælles EntryID)
                    unsigned char ID = iter->getIDEntry();

                    if((iter->storeEntry(valgteDag,Entry(ID,startHour,startMin,1))==true) &&
                       (iter->storeEntry(valgteDag,Entry(ID,endHour,endMin,0))==true))//Tilføjer start tidsplan
                    {
                         msgBox.setText("Tilføjelse af enheden succesfuld");
                    }
                    else
                         msgBox.setText("Det maksimale antal tidsplaner for enkle dag er nået");

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
