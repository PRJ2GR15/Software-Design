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


//=============================================================
// METHOD : Explicit Constructor
// DESCR. : 
//=============================================================


EditUnit::EditUnit(QStackedWidget *parent, UnitRegister &regRef, CommInterface& commRef) :
    QWidget(parent), invalidSelection(9999),
    ui(new Ui::EditUnit)
{
    ui->setupUi(this);
    this->setAccessibleName("Edit Unit");
    this->findChild<QLineEdit*>("newUnitID_LineEdit")->setValidator(new QIntValidator(1,255));
    this->findChild<QLineEdit*>("newRoomID_LineEdit")->setValidator(new QIntValidator(-1,255));
    this->findChild<QLineEdit*>("newUnitID_LineEdit")->setPlaceholderText("empty");
    this->findChild<QLineEdit*>("newRoomID_LineEdit")->setPlaceholderText("empty");
    parentPtr = parent;
    setRegistryPtr(regRef);
    setCommPtr(commRef);
    selectedUnitID = -1; selectedRoomID = -1;
    setTablePtr(this->findChild<QTableWidget*>("editUnit_Table"));
}

//=============================================================
// METHOD : Deconstructor
// DESCR. : 
//=============================================================


EditUnit::~EditUnit()
{
    delete ui;
}

//=============================================================
// METHOD : setSelectedUnitID
// DESCR. : Funktionen benyttes for at sætte attributten selectedUnitID
//=============================================================


void EditUnit::setSelectedUnitID(int unitID) {
    selectedUnitID = unitID;
}

//=============================================================
// METHOD : setTablePtr
// DESCR. : Funktionen sætter en pointer til tabellen
//=============================================================


void EditUnit::setTablePtr(QTableWidget* tableRef)
{
    if(tableRef != NULL) {
        tablePtr = tableRef;
    }
    else
        cerr << "Couldn't register table address" << endl;
}

//=============================================================
// METHOD : updateTable
// DESCR. : Funktionen opdaterer tabellen med tilføjede enheder
//=============================================================


void EditUnit::updateTable()
{
    selectedUnitID = -1; selectedRoomID = -1;
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
                rowCount += 1;
            }
        }
}

//=============================================================
// METHOD : on_editUnit_Cancel_PushButton_clicked
// DESCR. : Funktionen afbryder redigering af enheder 
//=============================================================


void EditUnit::on_editUnit_Cancel_PushButton_clicked()
{
    parentPtr->setCurrentIndex(0);
}

//=============================================================
// METHOD : on_editUnit_Cancel_PushButton_clicked
// DESCR. : Funktionen sætter hvilken celle som er valgt i tabellen
//=============================================================


void EditUnit::on_editUnit_Table_cellClicked(int row, int column)
{
    selectedRow = row;
    QModelIndex index = tablePtr->model()->index(selectedRow,0,QModelIndex());
    QString data = tablePtr->model()->data(index).toString();
    selectedUnitID = static_cast<char>(data.toInt());
    if(this->findChild<QLineEdit*>("currentUnitID_LineEdit") != 0)
            this->findChild<QLineEdit*>("currentUnitID_LineEdit")->setText(data);

    index = tablePtr->model()->index(selectedRow,1,QModelIndex());
    data = tablePtr->model()->data(index).toString();
    selectedRoomID = static_cast<char>(data.toInt());
    if(this->findChild<QLineEdit*>("currentRoomID_LineEdit") != 0)
        this->findChild<QLineEdit*>("currentRoomID_LineEdit")->setText(data);

    if(this->findChild<QLineEdit*>("newUnitID_LineEdit") != 0)
        this->findChild<QLineEdit*>("newUnitID_LineEdit")->clear();

    if(this->findChild<QLineEdit*>("newRoomID_LineEdit") != 0)
        this->findChild<QLineEdit*>("newRoomID_LineEdit")->clear();

}

//=============================================================
// METHOD : on_editUnit_Save_PushButton_clicked
// DESCR. : Funktionen gemmer ændringer af eksisterende enhed
//=============================================================


void EditUnit::on_editUnit_Save_PushButton_clicked()
{
    int newUnitID, newRoomID;
    if(selectedUnitID != -1 && selectedRoomID != -1)
    {
        newUnitID = selectedUnitID; newRoomID = selectedRoomID;
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Fejl under Ændring");
        msgBox.addButton(QMessageBox::Ok);
        msgBox.setText("Ingen enhed valg til ændring");
        if(msgBox.exec()==QMessageBox::Ok)
            return;
    }
    if(!this->findChild<QLineEdit*>("newUnitID_LineEdit")->text().isEmpty())
    {
        newUnitID = this->findChild<QLineEdit*>("newUnitID_LineEdit")->text().toInt();
    }

    if(!this->findChild<QLineEdit*>("newRoomID_LineEdit")->text().isEmpty())
    {
        newRoomID = this->findChild<QLineEdit*>("newRoomID_LineEdit")->text().toInt();
    }

    if(newUnitID == selectedUnitID && newRoomID == selectedRoomID)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Fejl under Ændring");
        msgBox.addButton(QMessageBox::Ok);
        msgBox.setText("Ingen enheds ændringer registreret.");
        if(msgBox.exec()==QMessageBox::Ok)
            return;
    }
    else
    {
        getRegistryPtr()->modifyUnit(static_cast<uchar>(selectedUnitID), static_cast<uchar>(newUnitID), static_cast<uchar>(newRoomID));
        getCommPtr()->editUnit(static_cast<uchar>(selectedUnitID), static_cast<uchar>(newUnitID), static_cast<uchar>(newRoomID));
        QMessageBox msgBox;
        msgBox.setWindowTitle("Ændring Godkendt");
        msgBox.addButton(QMessageBox::Ok);
        msgBox.setText("Enhed: " + QString::number(selectedUnitID) + " opdateret til\nEnheds ID: " + QString::number(newUnitID) + "\n" + "Rum ID: " + QString::number(newRoomID));
        if(msgBox.exec()==QMessageBox::Ok)
        {
            updateTable();
            return;
        }
    }
}
