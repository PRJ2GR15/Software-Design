#include "removeentry.h"
#include "ui_removeentry.h"

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

RemoveEntry::~RemoveEntry()
{
    delete ui;
}

void RemoveEntry::getUnit(int id)
{
    unitID=id;
}

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

                    int dayCounter = 0;
                    int rowCounter = 0;

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
void RemoveEntry::on_RemoveEntry_2_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Fejl under Ændring");
    msgBox.addButton(QMessageBox::Ok);

    if(selectedRow != -1)
    {
        map<unsigned char,int>::iterator it = next(myMap.begin(), selectedRow);
        entryID = +it->first;
    }
    else
    {
        {
            msgBox.setText("Ingen tidsplan valgt til ændring");
            if(msgBox.exec()==QMessageBox::Ok)
                return;
        }
    }

    // Hvilken dag er det på valgte entry i tabelen.

    QString DayEntry = ui->EntriesTable->item(selectedRow,0)->text();

    int DayIntEntry=0;

    if(DayEntry=="Mandag")
         DayIntEntry=0;
    else if(DayEntry=="Tirsdag")
         DayIntEntry=1;
    else if(DayEntry=="Onsdag")
         DayIntEntry=2;
    else if(DayEntry=="Torsdag")
         DayIntEntry=3;
    else if(DayEntry=="Fredag")
         DayIntEntry=4;
    else if(DayEntry=="Lørdag")
         DayIntEntry=5;
    else
         DayIntEntry=6;

vector<Unit>::iterator iter;
for(iter = getRegistryPtr()->begin(); iter != getRegistryPtr()->end(); ++iter)
 {
    if(iter->getUnitID()==unitID)
    {
        vector< vector<Entry> > myRef = iter->getEntryRegisterRef();

         for(int j = myRef[DayIntEntry].size()-1; j>= 0; j--)
         {
            if(myRef[DayIntEntry][j].EntryID() == entryID)
            {
                 iter->addDeletedEntry(entryID);
                 iter->deleteEntry(DayIntEntry,j);
            }
         }

         msgBox.setText("Tidsplanen er fjernet");
         if(msgBox.exec()==QMessageBox::Ok)
         parentPtr->setCurrentIndex(0);
    }
  }
}




void RemoveEntry::on_EntriesTable_cellClicked(int row, int column)
{
    selectedRow = row;
}

void RemoveEntry::on_Annuller_clicked()
{
    parentPtr->setCurrentIndex(0);
}

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
         msgBox.setText("Tidsplanen er fjernet");
         if(msgBox.exec()==QMessageBox::Ok)
         parentPtr->setCurrentIndex(0);
    }
  }


}
