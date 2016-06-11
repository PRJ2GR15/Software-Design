#include "addentry.h"
#include "ui_addentry.h"
#include "entry.h"
#include <QInputDialog>

//=============================================================
// METHOD : Explicit Constructor
// DESCR. : 
//=============================================================


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

//=============================================================
// METHOD : Deconstructor
// DESCR. : 
//=============================================================


AddEntry::~AddEntry()
{
    delete ui;
}

//=============================================================
// METHOD : getUnit	
// DESCR. : Slot som modtager UnitID der skal redigeres på
//=============================================================


void AddEntry::getUnit(int id)
{
    unitID=id;
}

//=============================================================
// METHOD : setTablePtr
// DESCR. : Sætter en pointer til tabellen
//=============================================================


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

//=============================================================
// METHOD : populateTable
// DESCR. : Funktionen fylder tabellen med tilføjede tidsplaner
//=============================================================


void AddEntry::populateTable()
{
    int rows=2;//Da starttid og sluttids udfyldes på en linje, men hentes ind som to.
    int rowCount =0;
    QString inf;

    //Sørg for at registry pointer er sat
    if(getRegistryPtr() != NULL)
        //Sørg for at tablePtr er sat
        if(tablePtr != NULL)
        {
            vector<Unit>::iterator iter;
            //Gennemløber unitRegister ved at hente et par iterators.
            for(iter = getRegistryPtr()->begin(); iter != getRegistryPtr()->end(); ++iter)
            {
                //Hvis enheden med unitID valgt under "EditEntry" menuen er fundet
                if(iter->getUnitID()==unitID)
                {
                    //
                    tablePtr->setRowCount(iter->getSize()/rows);
                    vector< vector<Entry> > myRef = iter->getEntryRegisterRef();
                    int dayCounter = 0;
                    int rowCounter = 0;
                    map<unsigned char, int> myMap;
                    map<int, string> dayMap = { {0, "Mandag"}, {1, "Tirsdag"}, {2, "Onsdag"}, {3, "Torsdag"}, {4, "Fredag"}, {5, "Lørdag"}, {6, "Søndag"} };
                    for(auto day : myRef) {
                        for(auto entry : day) {
                            inf = QString::fromStdString(dayMap[dayCounter]);
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

//=============================================================
// METHOD : on_cancel_clicked
// DESCR. : Funktionen afbryder tilføjelse af tidsplan til enheden
//=============================================================


void AddEntry::on_Cancel_clicked()
{
    parentPtr->setCurrentIndex(0);
}

//=============================================================
// METHOD : on_AddTheEntry_clicked
// DESCR. : Funktionen tilføjer tidsplan til enheden
//=============================================================

void AddEntry::on_AddTheEntry_clicked()
{
    map<QString, int> dayMap = { {"Mandag", 0}, {"Tirsdag", 1}, {"Onsdag", 2}, {"Torsdag", 3},
                                  {"Fredag", 4}, {"Lørdag", 5}, {"Søndag", 6} };
    QString date = ui->comboBox->currentText();

    int selectedDay = dayMap[date];
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
                unsigned char ID = iter->getIDEntry();
                Entry tmpStartEntry(ID, startHour, startMin, 1); Entry tmpStopEntry(ID, endHour, endMin, 0);
                if( (iter->compareEntry(tmpStartEntry, selectedDay) == false) && (iter->compareEntry(tmpStopEntry, selectedDay) ) == false)
                {
                    if( iter->storeEntry(selectedDay, tmpStartEntry) )
                    {
                        iter->storeEntry(selectedDay, tmpStopEntry);
                        msgBox.setText("Tilføjelse af enheden godkendt");
                        if(msgBox.exec()==QMessageBox::Ok)
                            parentPtr->setCurrentIndex(0);
                    }
                    else
                    {
                        iter->addDeletedEntry(ID);
                        msgBox.setText("Tilføjelse af enheden fejlede");
                        if(msgBox.exec()==QMessageBox::Ok)
                            parentPtr->setCurrentIndex(0);
                    }
                }
                else
                {
                    iter->addDeletedEntry(ID);
                    msgBox.setText("Tilføjelse af enheden fejlede");
                    if(msgBox.exec()==QMessageBox::Ok)
                        parentPtr->setCurrentIndex(0);
                }

            }

        }
    }
    else
    {
        msgBox.setText("Tilføjelse af enheden fejlede");
        if(msgBox.exec()==QMessageBox::Ok)
            parentPtr->setCurrentIndex(0);
    }
}
