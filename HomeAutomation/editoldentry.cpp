#include "editoldentry.h"
#include "ui_editoldentry.h"

EditOldEntry::EditOldEntry(QStackedWidget *parent, UnitRegister& regRef, CommInterface& commRef) :
    QWidget(parent),
    ui(new Ui::EditOldEntry)
{
    ui->setupUi(this);
    this->setAccessibleName("Edit Old Entry");
}

EditOldEntry::~EditOldEntry()
{
    delete ui;
}
