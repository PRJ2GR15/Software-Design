#include "editentry.h"
#include "ui_editentry.h"

EditEntry::EditEntry(QWidget *parent, UnitRegister& regRef, CommInterface& commRef) :
    QWidget(parent),
    ui(new Ui::EditEntry)
{
    ui->setupUi(this);
    this->setAccessibleName("Edit Entry");
}

EditEntry::~EditEntry()
{
    delete ui;
}
