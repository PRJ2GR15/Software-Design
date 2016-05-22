#include "editunit.h"
#include "ui_editunit.h"

//========================================================================
// FILENAME : <EditUnit.cpp>
// CREATED : <21/05-2016>
// AUTHOR : <Nikolai James Topping>
// DESCR. : <Implementering af EditUnit menuen>
//
//------------------------------------------------------------------------
//
// REV. DATE/AUTHOR CHANGE DESCRIPTION
// 1.0 <21-05/2016/Nikolai J. Topping> <Oprettet fil.>
//========================================================================

EditUnit::EditUnit(QStackedWidget *parent, UnitRegister &regRef, CommInterface& commRef) :
    QWidget(parent), invalidSelection(9999),
    ui(new Ui::EditUnit)
{
    ui->setupUi(this);
    this->setAccessibleName("Edit Unit");
    this->findChild<QLineEdit*>("newUnitID_LineEdit")->setValidator(new QIntValidator(1,255));
    this->findChild<QLineEdit*>("newRoomID_LineEdit")->setValidator(new QIntValidator(1,255));
    parentPtr = parent;
    setRegistryPtr(regRef);
    setCommPtr(commRef);
    setTablePtr(this->findChild<QTableWidget*>("editUnit_Table"));
}

EditUnit::~EditUnit()
{
    delete ui;
}

void EditUnit::setSelectedUnitID(unsigned char unitID) {
    selectedUnitID = unitID;
}

void EditUnit::setTablePtr(QTableWidget* tableRef)
{
    if(tableRef != NULL) {
        tablePtr = tableRef;
    }
    else
        cerr << "Couldn't register table address" << endl;
}

/*void EditUnit::populateTable() {
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
}*/

void EditUnit::updateTable()
{
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

void EditUnit::on_editUnit_Cancel_PushButton_clicked()
{
    parentPtr->setCurrentIndex(0);
}

void EditUnit::on_editUnit_Table_cellClicked(int row, int column)
{
    selectedRow = row;
    QModelIndex index = tablePtr->model()->index(selectedRow,0,QModelIndex());
    QString data = tablePtr->model()->data(index).toString();
    this->findChild<QLineEdit*>("currentUnitID_LineEdit")->setText(data);
    selectedUnitID = static_cast<char>(data.toInt());

    index = tablePtr->model()->index(selectedRow,1,QModelIndex());
    data = tablePtr->model()->data(index).toString();
    this->findChild<QLineEdit*>("currentRoomID_LineEdit")->setText(data);
    selectedRoomID = static_cast<char>(data.toInt());

}
