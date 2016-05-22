#include "addentry.h"
#include "ui_addentry.h"

AddEntry::AddEntry(QStackedWidget *parent, UnitRegister& regRef, CommInterface& commRef) :
    QWidget(parent),
    ui(new Ui::AddEntry)
{
    ui->setupUi(this);
    this->setAccessibleName("Add Entry");
}

AddEntry::~AddEntry()
{
    delete ui;
}
