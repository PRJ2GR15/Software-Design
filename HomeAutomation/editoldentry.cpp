#include "editoldentry.h"
#include "ui_editoldentry.h"

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

EditOldEntry::~EditOldEntry()
{
    delete ui;
}

void EditOldEntry::getUnit(int id)
{
    unitID=id;
}

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
                    iter->printEntry();
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
                                    QString tmpQString = QString::number(+entry.getHour());
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
                                    QString tmpQString = QString::number(+entry.getHour());
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




void EditOldEntry::on_EditEntryTable_cellClicked(int row, int column)
{
    selectedRow=row;

    cout << selectedRow;



}

void EditOldEntry::on_Annuller_clicked()
{

}

void EditOldEntry::on_SaveEntry_clicked()
{

    map<unsigned char,int>::iterator it = next(myMap.begin(),selectedRow);
    entryID = +it->first;


    QString date = ui->DayBox->currentText();
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
    int EditstartHour = ui->EditStartTime->time().hour();
    int EditstartMin = ui->EditStartTime->time().minute();
    //Få slutid
    int EditendHour = ui->EditEndTime->time().hour();
    int EditendMin = ui->EditEndTime->time().minute();

     vector<Unit>::iterator iter;

     QMessageBox msgBox;
     msgBox.setWindowTitle("Udført funktion");
     msgBox.addButton(QMessageBox::Ok);

     if((EditstartHour<EditendHour)||((EditstartMin==EditendMin)& (EditstartMin<EditendMin)))
    {
         for(iter = getRegistryPtr()->begin(); iter != getRegistryPtr()->end(); ++iter)
         {
             if(iter->getUnitID()==unitID)
             {
                if((iter->compareEntry(Entry(iter->getEntryID(),EditstartHour,EditstartMin,1),valgteDag)==false) && (iter->compareEntry(Entry(iter->getEntryID(),EditendHour,EditendMin,0),valgteDag))==false)
                     {
                   vector< vector<Entry> > myRef = iter->getEntryRegisterRef();
                   for (auto row : myRef)
                       {
                           for (auto entry : row)
                         {

                            if(entry.EntryID()==entryID)
                            {
                                entry.print();

                                 cout << "test" <<endl;
                                if(entry.getAction()==1)
                                {
                                    if((entry.setHour(EditstartHour)==true)&& entry.setMin(EditstartMin)==true);
                                    msgBox.setText("Test 1 ");
                                }
                                else
                                       msgBox.setText("Tilføjelse af enheden fejlede1");

                                if(entry.getAction()==0)
                                {
                                    if((entry.setHour(EditendHour))==true && (entry.setMin(EditendMin)==true));
                                    msgBox.setText("Test 2 ");
                                    iter->countEntryID();
                                }

                                else
                                       msgBox.setText("Tilføjelse af enheden fejlede2");
                            }
                        }
                 }
            }

        }
     }


   if(msgBox.exec()==QMessageBox::Ok)
    parentPtr->setCurrentIndex(0);

}
}
