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




void EditOldEntry::on_EditEntryTable_cellClicked(int row, int column)
{
    selectedRow=row;
}

void EditOldEntry::on_Annuller_clicked()
{
     parentPtr->setCurrentIndex(0);
}

void EditOldEntry::on_SaveEntry_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Fejl under Ændring");
    msgBox.addButton(QMessageBox::Ok);

    if(selectedRow!=-1)
    {
        map<unsigned char,int>::iterator it = next(myMap.begin(),selectedRow);
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


    //Få hvilken dag som brugeren ønsker ændret til.

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


                    //Få den gamle dag
                         int OldEntryDag=0;

       QString OldEntry = ui->EditEntryTable->item(selectedRow,0)->text();




                     if(OldEntry=="Mandag")
                          OldEntryDag=0;
                     else if(OldEntry=="Tirsdag")
                          OldEntryDag=1;
                     else if(OldEntry=="Onsdag")
                          OldEntryDag=2;
                     else if(OldEntry=="Torsdag")
                          OldEntryDag=3;
                     else if(OldEntry=="Fredag")
                          OldEntryDag=4;
                     else if(OldEntry=="Lørdag")
                          OldEntryDag=5;
                     else
                          OldEntryDag=6;


    //Få hvilken tid som brugeren ønsker ændret til

      int EditstartHour = ui->EditStartTime->time().hour();
      int EditstartMin = ui->EditStartTime->time().minute();
                        //Få slutid
      int EditendHour = ui->EditEndTime->time().hour();
      int EditendMin = ui->EditEndTime->time().minute();

 //validering af tiden

      vector<Unit>::iterator iter;

      if((EditstartHour<EditendHour)||((EditstartHour==EditendHour)& (EditstartMin<EditendMin)))
           {
             for(iter = getRegistryPtr()->begin(); iter != getRegistryPtr()->end(); ++iter)
                {
                  if(iter->getUnitID()==unitID) // Finder den rigtige Unit udfra UnitID
                   {
                     // Tjekker at tidsplanen i forvejen ikke ligger i systemet
                     if((iter->compareEntry(Entry(iter->getEntryID(),EditstartHour,EditstartMin,1),valgteDag)==false) && (iter->compareEntry(Entry(iter->getEntryID(),EditendHour,EditendMin,0),valgteDag))==false)
                       {
            //Tjekke om den ønskede dag er ens
            vector< vector<Entry> > myRef = iter->getEntryRegisterRef();

                    //Hvis dagene er ens
             if(date==ui->EditEntryTable->item(selectedRow,0)->text())
                {


                    for(int j = 0; j<myRef[valgteDag].size();++j)
                    {
                        if(myRef[valgteDag][j].EntryID()==entryID)
                        {
                            if(myRef[valgteDag][j].getAction()==1)
                            {
                                    iter->updateEntry(valgteDag,j,EditstartHour,EditstartMin);
                            }
                            else
                            {    if(iter->updateEntry(valgteDag,j,EditendHour,EditendMin)==true)
                                    {
                                        msgBox.setText("Tidsplanen er nu opdateret");
                                        if(msgBox.exec()==QMessageBox::Ok)
                                        parentPtr->setCurrentIndex(0);
                                    }
                            }
                        }
                    }
                }
                                  //Hvis det ikke er samme dag.
              else
               {


                 for(int j = myRef[OldEntryDag].size()-1; j>=0;j--)
                 {

                     if(myRef[OldEntryDag][j].EntryID()==entryID)
                     {

                         if(myRef[OldEntryDag][j].getAction()==1)
                         {

                                 iter->deleteEntry(OldEntryDag,j);
                                 iter->storeEntry(valgteDag,Entry(entryID,EditstartHour,EditstartMin,1));
                                 iter->printEntry();
                         }
                         else
                         {
                                 iter->deleteEntry(OldEntryDag,j);
                                 if(iter->storeEntry(valgteDag,Entry(entryID,EditendHour,EditendMin,0))==true)
                                 {
                                     msgBox.setText("Tidsplanen er nu opdateret");
                                     if(msgBox.exec()==QMessageBox::Ok)
                                     parentPtr->setCurrentIndex(0);
                                 }
                        }
                     }
                 }

               }
                     }
                    else
                    {
                     msgBox.setText("Tiden findes allerede i tidsplanen");
                     if(msgBox.exec()==QMessageBox::Ok)
                     return;
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


