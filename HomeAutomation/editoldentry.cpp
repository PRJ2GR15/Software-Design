#include "editoldentry.h"
#include "ui_editoldentry.h"

//=============================================================
// METHOD : Explicit Constructor
// DESCR. : 
//=============================================================


EditOldEntry::EditOldEntry(QStackedWidget *parent, UnitRegister& regRef, CommInterface& commRef) :
    QWidget(parent),
    ui(new Ui::EditOldEntry)
{
    ui->setupUi(this);
    this->setAccessibleName("Edit Old Entry");

        parentPtr = parent;
        setRegistryPtr(regRef);
        setCommPtr(commRef);

        setTablePtr(this->findChild<QTableWidget*>("EditEntryTable"));
        populateTable();
}

//=============================================================
// METHOD : Deconstructor
// DESCR. : 
//=============================================================


EditOldEntry::~EditOldEntry()
{
    delete ui;
}

//=============================================================
// METHOD : getUnit
// DESCR. : Slot som modtager UnitID der skal redigeres på
//=============================================================


void EditOldEntry::getUnit(int id)
{
    unitID=id;
}

//=============================================================
// METHOD : setTablePtr
// DESCR. : Funktionen sætter en pointer til tabellen. Benyttes for at tilgå tabellen.
//=============================================================


void EditOldEntry::setTablePtr(QTableWidget* tableRef) {
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
// DESCR. : Funktionen udfylder tabellen med tilføjede tidsplaner. 
//=============================================================

void EditOldEntry::populateTable()
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
                                cout << "EditOldEntry::populateTable() : Entry ID: " << +entry.EntryID() << " Mapped to row : " << rowCounter << endl;
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
// METHOD : on_EditEntryTable_cellClicked
// DESCR. : Funktionen sætter hvilken celle som er valgt i tabellen
//=============================================================

void EditOldEntry::on_EditEntryTable_cellClicked(int row, int column)
{
    selectedRow=row;
    for(auto it = myMap.begin(); it != myMap.end(); ++it)
    {
        if(it->second == selectedRow)
            entryID = +it->first;
    }
}

//=============================================================
// METHOD : on_Annuller_clicked
// DESCR. : Funktionen afbryder redigering af eksisterende tidsplan
//=============================================================

void EditOldEntry::on_Annuller_clicked()
{
     parentPtr->setCurrentIndex(0);
}

//=============================================================
// METHOD : on_SaveEntry_clicked
// DESCR. : Funktionen gemmer ændringer af eksisterende tidsplan
//=============================================================

void EditOldEntry::on_SaveEntry_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Fejl under Ændring");
    msgBox.addButton(QMessageBox::Ok);
    //Check om der er valgt en row.
    if(selectedRow == -1)
    {
        msgBox.setText("Ingen tidsplan valgt til ændring");
        if(msgBox.exec()==QMessageBox::Ok)
        {
            return;
        }
    }

    //Få hvilken dag som brugeren ønsker ændret til.
    map<QString, int> dayMap = { {"Mandag", 0}, {"Tirsdag", 1}, {"Onsdag", 2}, {"Torsdag", 3},
                                  {"Fredag", 4}, {"Lørdag", 5}, {"Søndag", 6} };
    QString date = ui->DayBox->currentText();
    int selectedDay = dayMap[date];
    cout << "editOldEntry::SaveEntry_clicked : " << selectedDay << endl;

    //Få hvilken tid som brugeren ønsker ændret til
    int startHour = ui->EditStartTime->time().hour();
    int startMin = ui->EditStartTime->time().minute();
    //Få slutid
    int endHour = ui->EditEndTime->time().hour();
    int endMin = ui->EditEndTime->time().minute();

    //validering af tiden
    vector<Unit>::iterator iter;


    if( ( startHour < endHour ) || ( ( startHour == endHour ) && ( startMin < endMin ) ) )
    {
        for(iter = getRegistryPtr()->begin(); iter != getRegistryPtr()->end(); ++iter)
        {
            if(iter->getUnitID()==unitID) // Finder den rigtige Unit udfra UnitID
            {
                iter->deleteEntry(entryID);
                unsigned char newEntryID = iter->getIDEntry();
                iter->storeEntry(selectedDay, Entry(newEntryID, startHour, startMin, 1) );
                iter->storeEntry(selectedDay, Entry(newEntryID, endHour, endMin, 0) );
                msgBox.setText("Tidsplanen er nu opdateret");
                if(msgBox.exec()==QMessageBox::Ok)
                {
                    parentPtr->setCurrentIndex(0);
                }
            }
        }
    }
    else
    {
        msgBox.setText("Ugyldigt tidspunkt - sluttidspunkt før starttidspukt");
        if(msgBox.exec()==QMessageBox::Ok)
            return;
    }
}


