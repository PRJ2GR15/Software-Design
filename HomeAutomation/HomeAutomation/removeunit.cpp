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
    QWidget(parent),
    ui(new Ui::RemoveUnit)
{
    ui->setupUi(this);
    parentPtr = parent;
    setRegistryPtr(regRef);
    setCommPtr(commRef);
}

RemoveUnit::~RemoveUnit()
{
    delete ui;
}

void RemoveUnit::on_rem_u_PushButton_clicked()
{
    getParentPtr()->setCurrentIndex(0);
}
