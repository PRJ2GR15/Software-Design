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
    Q_OBJECT

public:
    EditUnit(QStackedWidget *parent, UnitRegister& regRef, CommInterface& commRef);
    ~EditUnit();

    void setSelectedUnitID(unsigned char);
    unsigned char getSelectedUnitID() { return selectedUnitID; };

    void setTablePtr(QTableWidget* tableRef);
    QTableWidget* getTablePtr() { return tablePtr; }

    //void populateTable();

public slots:
    void updateTable();

private slots:
    void on_pushButton_clicked();

private:
    Ui::EditUnit *ui;
    unsigned char selectedUnitID;
    QTableWidget* tablePtr;
};

#endif // EDITUNIT_H
