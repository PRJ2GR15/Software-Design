#include "removeentry.h"
#include "ui_removeentry.h"

//=============================================================
// METHOD : RemoveEntry
// DESCR. : Explicit Constructor
//=============================================================
RemoveEntry::RemoveEntry(QStackedWidget *parent, UnitRegister &regRef, CommInterface &commRef) :
    QWidget(parent),
    ui(new Ui::RemoveEntry)
{
    ui->setupUi(this);
    this->setAccessibleName("Remove Entry");
    parentPtr = parent;
    setRegistryPtr(regRef);
    setCommPtr(commRef);

    setTablePtr(this->findChild<QTableWidget*>("EntriesTable"));
    populateTable();
}

//=============================================================
// METHOD : ~RemoveEntry
// DESCR. : Destructor
//=============================================================
RemoveEntry::~RemoveEntry()
{
    delete ui;
}

//=============================================================
// METHOD : getUnit
// DESCR. : Slot som modtager ID for den Unit der skal redigeres
//=============================================================
void RemoveEntry::getUnit(int id)
{
    unitID=id;
}

//=============================================================
// METHOD : setTablePtr
// DESCR. : Sætter pointeren til tabellen vist i UI
//=============================================================
void RemoveEntry::setTablePtr(QTableWidget* tableRef) {
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
// DESCR. : Udfylder tabellen med relevant information
//=============================================================
void RemoveEntry::populateTable()
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

                    tablePtr->setRowCount(iter->getSize()/rows);
                    vector< vector<Entry> > myRef = iter->getEntryRegisterRef();
                    map<int, QString> dayMap = { {0, "Mandag"}, {1, "Tirsdag"}, {2, "Onsdag"}, {3, "Torsdag"}, {4, "Fredag"}, {5, "Lørdag"}, {6, "Søndag"} };
                    int dayCounter = 0;
                    int rowCounter = 0;

                    for(auto day : myRef) {
                        for(auto entry : day) {
                            inf = dayMap[dayCounter];
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
// METHOD : on_RemoveEntry_2_clicked
// DESCR. : Slot der kaldes når der trykkes på "Fjern Tidsplan"
//=============================================================
void RemoveEntry::on_RemoveEntry_2_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Fejl under Ændring");
    msgBox.addButton(QMessageBox::Ok);

    if(selectedRow == -1)
    {
        msgBox.setText("Ingen tidsplan valgt til ændring");
        if(msgBox.exec()==QMessageBox::Ok)
            return;
    }

    vector<Unit>::iterator iter;
    for(iter = getRegistryPtr()->begin(); iter != getRegistryPtr()->end(); ++iter)
    {
        if(iter->getUnitID()==unitID)
        {
            iter->deleteEntry(entryID);
            msgBox.setText("Tidsplanen er fjernet");
            if(msgBox.exec()==QMessageBox::Ok)
                parentPtr->setCurrentIndex(0);
        }
    }
}

//=============================================================
// METHOD : on_EntriesTable_cellClicked
// DESCR. : Slot der kaldes når der trykkes på et element i tabellen
//=============================================================
void RemoveEntry::on_EntriesTable_cellClicked(int row, int column)
{
    selectedRow = row;
    for(auto it = myMap.begin(); it != myMap.end(); ++it)
    {
        if(it->second == selectedRow)
            entryID = +it->first;
    }
}

//=============================================================
// METHOD : on_Annuller_clicked
// DESCR. : Slot der kaldes når der trykkes annuller
//=============================================================
void RemoveEntry::on_Annuller_clicked()
{
    parentPtr->setCurrentIndex(0);
}

//=============================================================
// METHOD : on_RemoveEntriesForDay_clicked
// DESCR. : Slot der kaldes når der trykkes "Fjern tidsplan for valgte dag"
//=============================================================
void RemoveEntry::on_RemoveEntriesForDay_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Fjerne tidsplan");
    msgBox.addButton(QMessageBox::Ok);

    QString date = ui->ComboDayBox->currentText();

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

    vector<Unit>::iterator iter;

for(iter = getRegistryPtr()->begin(); iter != getRegistryPtr()->end(); ++iter)
 {
    if(iter->getUnitID()==unitID)
    {

        vector< vector<Entry> > myRef = iter->getEntryRegisterRef();

         for(int j = myRef[valgteDag].size()-1; j>= 0; j--)
         {
            if(myRef[valgteDag][j].getAction()==1) // Vi ved at der findes to med samme id.
             {
                 iter->addDeletedEntry(myRef[valgteDag][j].EntryID());
             }
         }

         iter->deleteDayEntry(valgteDag);
         msgBox.setText("Dagen er ryddet.");
         if(msgBox.exec()==QMessageBox::Ok)
         parentPtr->setCurrentIndex(0);
    }
  }


}
