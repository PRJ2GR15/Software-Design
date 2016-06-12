//========================================================================
// FILENAME : <RemoveUnit.cpp>
// CREATED : <18/05-2016>
// AUTHOR : <Nikolai James Topping>
// DESCR. : <Implementering af MainMenu>
//
//------------------------------------------------------------------------
//
// REV. DATE/AUTHOR CHANGE DESCRIPTION
// 1.0 <18.05/2016/Nikolai J. Topping> <Oprettet RemoveUnit>
//
//========================================================================

#include "removeunit.h"
#include "ui_removeunit.h"

//=============================================================
// METHOD : RemoveUnit
// DESCR. : Explicit Constructor
//=============================================================
RemoveUnit::RemoveUnit(QStackedWidget *parent, UnitRegister& regRef, CommInterface& commRef) :
    QWidget(parent), invalidSelection(9999),
    ui(new Ui::RemoveUnit)
{
    ui->setupUi(this);
    this->setAccessibleName("Remove Unit");
    parentPtr = parent;
    setRegistryPtr(regRef);
    setCommPtr(commRef);
    setTablePtr(this->findChild<QTableWidget*>("rem_unitTable"));
    selectedRow = invalidSelection;
}

//=============================================================
// METHOD : ~RemoveUnit
// DESCR. : Destructor
//=============================================================
RemoveUnit::~RemoveUnit()
{
    delete ui;
}

//=============================================================
// METHOD : setTablePtr
// DESCR. : Sætter pointeren til UI'ets tabel.
//=============================================================
void RemoveUnit::setTablePtr(QTableWidget* tableRef) {
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
// DESCR. : Udfylder tabellen med liste over enheder
//=============================================================
void RemoveUnit::populateTable() {
    if(getRegistryPtr() != NULL)
        if(tablePtr != NULL) {
            tablePtr->setRowCount(getRegistryPtr()->getRegistrySize());
            int rowCount = 0;
            vector<Unit>::iterator iter;
            QString inf;
            for(iter = getRegistryPtr()->begin(); iter != getRegistryPtr()->end(); ++iter) {
                //Returnere unitID som uchar, caster til int. QString::number gemmer int som en QString.
                inf = QString::number(+((*iter).getUnitID()));
                tablePtr->setItem( rowCount, 0, new QTableWidgetItem( inf ) );
                //Returnere RoomID som uchar, caster til int. QString::number gemmer int som en QString.
                inf = QString::number(+((*iter).getRoomID()));
                tablePtr->setItem( rowCount, 1, new QTableWidgetItem( inf ) );
                if(+((*iter).getStatus()))
                    inf = "Tændt";
                else
                    inf = "Slukket";
                tablePtr->setItem( rowCount, 2, new QTableWidgetItem( inf ) );
                rowCount += 1;
            }
        }
}

//=============================================================
// METHOD : on_rem_unitTable_cellClicked
// DESCR. : Slot der kaldes når der trykkes på en felt i tabellen
//=============================================================
void RemoveUnit::on_rem_unitTable_cellClicked(int row, int column)
{
    selectedRow = row;
}

//=============================================================
// METHOD : on_remove_PushButton_clicked
// DESCR. : Slot der kaldes når der trykkes på fjern enhed
//=============================================================
void RemoveUnit::on_remove_PushButton_clicked()
{
    QModelIndex index = tablePtr->model()->index(selectedRow,0,QModelIndex());
    int data = tablePtr->model()->data(index).toInt();
    if( getRegistryPtr()->deleteUnit(static_cast<uchar>(data)) )
    {
        getCommPtr()->deleteUnit(data);
        QMessageBox msgBox;
        msgBox.setWindowTitle("Enhed Fjernet");
        msgBox.addButton(QMessageBox::Ok);
        msgBox.setText("Enheden er blevet fjernet.");
        if(msgBox.exec()==QMessageBox::Ok)
        {
            populateTable();
            return;
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Fejl Under Fjernelse");
        msgBox.addButton(QMessageBox::Ok);
        msgBox.setText("Ingen enhed fjernet.");
        if(msgBox.exec()==QMessageBox::Ok)
        {
            populateTable();
            return;
        }
    }
    //getCommPtr()->deleteUnit(data);
    //populateTable();


}

//=============================================================
// METHOD : on_cancel_PushButton_clicked
// DESCR. : Slot der kaldes når der trykkes på annuller
//=============================================================
void RemoveUnit::on_cancel_PushButton_clicked()
{
    parentPtr->setCurrentIndex(0);
}
