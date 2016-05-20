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
    Q_OBJECT

public:
    explicit RemoveUnit(QStackedWidget *parent = 0, UnitRegister& regRef, CommInterface& commRef);
    ~RemoveUnit();

private slots:
    void on_rem_u_PushButton_clicked();

private:
    Ui::RemoveUnit *ui;
    //QWidget* parentPtr;
};

#endif // REMOVEUNIT_H
