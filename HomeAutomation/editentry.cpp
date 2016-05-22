#include "editentry.h"
#include "ui_editentry.h"

EditEntry::EditEntry(QStackedWidget *parent, UnitRegister& regRef, CommInterface& commRef) :
    QWidget(parent),
    ui(new Ui::EditEntry)
{
    ui->setupUi(this);
    this->setAccessibleName("Edit Entry");
    parentPtr = parent;
    setRegistryPtr(regRef);
    setCommPtr(commRef);
    setTablePtr(this->findChild<QTableWidget*>("EntryTable"));
    populateTable();
}

EditEntry::~EditEntry()
{
    delete ui;
}

void EditEntry::setTablePtr(QTableWidget* tableRef) {
    if(tableRef != NULL) {
        tablePtr = tableRef;
        //Sørger for at man ikke kan redigere i vores table.
        tablePtr->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tablePtr->setSelectionBehavior(QAbstractItemView::SelectRows);
        tablePtr->setSelectionMode(QAbstractItemView::SingleSelection);
    }
    else
        cerr << "Couldn't register table address" << endl;
}


void EditEntry::populateTable() {
    if(getRegistryPtr() != NULL)
        if(tablePtr != NULL) {
            tablePtr->setRowCount(getRegistryPtr()->getRegistrySize());
            int rowCount = 0;
            vector<Unit>::iterator iter;

            QString inf;
            QString size;
            for(iter = getRegistryPtr()->begin(); iter != getRegistryPtr()->end(); ++iter) {


                //Returnere unitID som uchar, caster til int. QString::number gemmer int som en QString.
                inf = QString::number(+((*iter).getUnitID()));
                tablePtr->setItem( rowCount, 0, new QTableWidgetItem( inf ) );


               size = QString::number(+(iter->getSize()));
               tablePtr->setItem(rowCount,1,new QTableWidgetItem(size));

                rowCount += 1;


            }
        }
}

void EditEntry::on_pushButton_clicked()
{
    for(int i = 0; i < getParentPtr()->count(); ++i) {
        if(getParentPtr()->widget(i)->accessibleName().compare("Add Entry") == 0) {
            getParentPtr()->setCurrentIndex(i);
            return;
        }
    }
    cerr<< "Kan ikke finde Add Entry" << endl;
}

void EditEntry::on_pushButton_2_clicked()
{
    for(int i = 0; i < getParentPtr()->count(); ++i) {
        if(getParentPtr()->widget(i)->accessibleName().compare("Edit Old Entry") == 0) {
            getParentPtr()->setCurrentIndex(i);
            return;
        }
    }
    cerr<< "Kan ikke finde Edit Old Entry" << endl;
}
