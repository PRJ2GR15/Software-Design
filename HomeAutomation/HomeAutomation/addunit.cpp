#include "addunit.h"
#include "ui_addunit.h"

AddUnit::AddUnit(QStackedWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddUnit)
{
    ui->setupUi(this);
    parentPtr = parent;
}

AddUnit::~AddUnit()
{
    delete ui;
}
