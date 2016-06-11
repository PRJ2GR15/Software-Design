#include "editentry.h"
#include "ui_editentry.h"


//=============================================================
// METHOD : Explicit Constructor
// DESCR. : 
//=============================================================


EditEntry::EditEntry(QStackedWidget *parent, UnitRegister& regRef, CommInterface& commRef) :
    QWidget(parent),
    ui(new Ui::EditEntry)
{
    ui->setupUi(this);
    this->setAccessibleName("Edit Entry");
    parentPtr = parent;
    setRegistryPtr(regRef);
    setCommPtr(commRef);
    setTablePtr(this->findChild<QTableWidget*>("EntryTable"));
    populateTable();

}

//=============================================================
// METHOD : Deconstructor
// DESCR. : 
//=============================================================


EditEntry::~EditEntry()
{
    delete ui;
}

//=============================================================
// METHOD : setTablePtr
// DESCR. : Funktionen sætter en pointer til tabellen
//=============================================================


void EditEntry::setTablePtr(QTableWidget* tableRef) {
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
// DESCR. : Funktionen udfylder tabellen med enheden
// samt hvor mange de enkelte enheder har af tidsplaner. 
//=============================================================


void EditEntry::populateTable() {
    if(getRegistryPtr() != NULL)
        if(tablePtr != NULL) {
            tablePtr->setRowCount(getRegistryPtr()->getRegistrySize());
            int rowCount = 0;
            vector<Unit>::iterator iter;

            QString inf;
            QString size;
            for(iter = getRegistryPtr()->begin(); iter != getRegistryPtr()->end(); ++iter) {


                //Returnere unitID som uchar, caster til int. QString::number gemmer int som en QString.
                inf = QString::number(+((*iter).getUnitID()));
                tablePtr->setItem( rowCount, 0, new QTableWidgetItem( inf ) );


               size = QString::number(+(iter->getSize()/2));
               tablePtr->setItem(rowCount,1,new QTableWidgetItem(size));

                rowCount += 1;


            }
        }
}

//=============================================================
// METHOD : on_EntryTable_cellClicked
// DESCR. : Funktionen sætter hvilken celle som er valgt i tabellen 
//=============================================================


void EditEntry::on_EntryTable_cellClicked(int row, int column)
{
    selectedRow=row;

    QModelIndex colNr = tablePtr->model()->index(selectedRow,1,QModelIndex());
    selectedCol = tablePtr->model()->data(colNr).toInt(); //Benyttes for at vide om der er nogle aktive tidsplaner at ændre.

}

//=============================================================
// METHOD : returnSelected
// DESCR. : Funktionen returner hvilken enhed som er valgt i tabellen
//=============================================================


void EditEntry::returnSelected()
{
    QModelIndex index = tablePtr->model()->index(selectedRow,0,QModelIndex());
    int data = tablePtr->model()->data(index).toInt();

    emit sendid(data);
}


//=============================================================
// METHOD : on_RemoveEntry_clicked
// DESCR. : Funktionen åbner ”Fjern tidsplan” vinduet
//=============================================================



void EditEntry::on_RemoveEntry_clicked()
{
    returnSelected();

    if(selectedRow!=-1 && selectedCol>0)
    {
    for(int i = 0; i < getParentPtr()->count(); ++i) {
        if(getParentPtr()->widget(i)->accessibleName().compare("Remove Entry") == 0) {
            getParentPtr()->setCurrentIndex(i);
            return;
        }
    }
    cerr<< "Kan ikke finde Remove Entry" << endl;
    }
    else{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Fejl under Ændring");
    msgBox.addButton(QMessageBox::Ok);
    if(selectedRow==-1)
    msgBox.setText("Ingen tidsplan valgt til ændring");
    else
        msgBox.setText("Ingen tidsplan at fjerne");
    if(msgBox.exec()==QMessageBox::Ok)
        return;
    }
}


//=============================================================
// METHOD : on_AddEntry_clicked
// DESCR. : Funktionen åbner ”Tilføj tidsplan” vinduet
//=============================================================


void EditEntry::on_AddEntry_clicked()
{
    returnSelected();
    if(selectedRow!=-1)
    {
        for(int i = 0; i < getParentPtr()->count(); ++i) {
            if(getParentPtr()->widget(i)->accessibleName().compare("Add Entry") == 0) {
                getParentPtr()->setCurrentIndex(i);
                return;
        }
    }
    cerr<< "Kan ikke finde Add Entry" << endl;
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Fejl under tilføjelse");
        msgBox.addButton(QMessageBox::Ok);
        msgBox.setText("Ingen enhed valg til tilføjelse af tidsplan");
        if(msgBox.exec()==QMessageBox::Ok)
            return;
    }
}


//=============================================================
// METHOD : on_ScheduleCancel_clicked
// DESCR. : Funktionen sender brugeren tilbage til mainWindow
//=============================================================


void EditEntry::on_ScheduleCancel_clicked()
{
    parentPtr->setCurrentIndex(0);
}

//=============================================================
// METHOD : on_EditSchedule_clicked
// DESCR. : Funktionen åbner ”Rediger eksisterende tidsplan” vinduet. 
//=============================================================



void EditEntry::on_EditSchedule_clicked()
{
    returnSelected();

    if(selectedRow!=-1 && selectedCol>0)
    {
    for(int i = 0; i < getParentPtr()->count(); ++i) {
        if(getParentPtr()->widget(i)->accessibleName().compare("Edit Old Entry") == 0) {
            getParentPtr()->setCurrentIndex(i);
            return;
        }
    }
    cerr<< "Kan ikke finde Edit Old Entry" << endl;
    }
    else{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Fejl under Ændring");
    msgBox.addButton(QMessageBox::Ok);
    if(selectedRow==-1)
    msgBox.setText("Ingen enhed valg til ændring");
    else
        msgBox.setText("Ingen tidsplan at ændre");
    if(msgBox.exec()==QMessageBox::Ok)
        return;
    }
}
