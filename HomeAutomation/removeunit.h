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

#ifndef REMOVEUNIT_H
#define REMOVEUNIT_H

#include <QWidget>
#include "UnitRegister.h"
#include "CommInterface.h"
#include "basemenu.h"

namespace Ui {
class RemoveUnit;
}

class RemoveUnit : public QWidget, public BaseMenu
{
    const int invalidSelection;
    Q_OBJECT

public:
    RemoveUnit(QStackedWidget *parent, UnitRegister& regRef, CommInterface& commRef);
    ~RemoveUnit();

    QTableWidget* getTablePtr() { return tablePtr; }

    void setTablePtr(QTableWidget* tableRef);

    void populateTable();

private slots:
    //void on_rem_unitTable_cellEntered(int row, int column);

    void on_rem_unitTable_cellClicked(int row, int column);

    void on_remove_PushButton_clicked();

    void on_cancel_PushButton_clicked();

private:
    Ui::RemoveUnit *ui;
    QTableWidget* tablePtr;
    int selectedRow, selectedColumn;
};

#endif // REMOVEUNIT_H
