#include "addunit.h"
#include "ui_addunit.h"

AddUnit::AddUnit(QStackedWidget *parent, UnitRegister &regRef, CommInterface &comRef) :
    QWidget(parent),
    ui(new Ui::AddUnit)
{
    ui->setupUi(this);
    parentPtr = parent;
    setRegistryPtr(regRef);
    setCommPtr(comRef);
}

AddUnit::~AddUnit()
{
    delete ui;
}
