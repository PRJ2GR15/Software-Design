#ifndef EDITUNIT_H
#define EDITUNIT_H

//========================================================================
// FILENAME : <EditUnit.h>
// CREATED : <21/05-2016>
// AUTHOR : <Nikolai James Topping>
// DESCR. : <Header filen for EditUnit>
//
//------------------------------------------------------------------------
//
// REV. DATE/AUTHOR CHANGE DESCRIPTION
// 1.0 <21-05/2016/Nikolai J. Topping> <Oprettet fil.>
//========================================================================
#include <QWidget>
#include "basemenu.h"

namespace Ui {
class EditUnit;
}

class EditUnit : public QWidget, public BaseMenu
{
    const int invalidSelection;
    Q_OBJECT

public:
    EditUnit(QStackedWidget *parent, UnitRegister& regRef, CommInterface& commRef);
    ~EditUnit();

    void setSelectedUnitID(int);
    unsigned char getSelectedUnitID() { return selectedUnitID; };

    void setTablePtr(QTableWidget* tableRef);
    QTableWidget* getTablePtr() { return tablePtr; }

    //void populateTable();

public slots:
    void updateTable();

private slots:

    void on_editUnit_Cancel_PushButton_clicked();

    void on_editUnit_Table_cellClicked(int row, int column);

    void on_editUnit_Save_PushButton_clicked();

private:
    Ui::EditUnit *ui;
    int selectedUnitID, selectedRoomID;
    int selectedRow;
    QTableWidget* tablePtr;
};

#endif // EDITUNIT_H
