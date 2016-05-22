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

RemoveUnit::~RemoveUnit()
{
    delete ui;
}

//=============================================================
// METHOD :
// DESCR. :
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

/*void RemoveUnit::on_rem_unitTable_cellEntered(int row, int column)
{
    selectedRow = row;
    selectedColumn = column;
}*/

void RemoveUnit::on_rem_unitTable_cellClicked(int row, int column)
{
    selectedRow = row;
}

void RemoveUnit::on_remove_PushButton_clicked()
{
    QModelIndex index = tablePtr->model()->index(selectedRow,0,QModelIndex());
    QString data = tablePtr->model()->data(index).toString();
    cout << data.toStdString() << endl;
    getRegistryPtr()->deleteUnit(static_cast<uchar>(data.toInt()));
    cout << "Unit with ID: " << data.toStdString() << " deleted." << endl;
    populateTable();
}

void RemoveUnit::on_cancel_PushButton_clicked()
{
    parentPtr->setCurrentIndex(0);
}
