//========================================================================
// FILENAME : <MainMenu.cpp>
// CREATED : <18/05-2016>
// AUTHOR : <Nikolai James Topping>
// DESCR. : <Implementering af MainMenu>
//
//------------------------------------------------------------------------
//
// REV. DATE/AUTHOR CHANGE DESCRIPTION
// 1.0 <18.05/2016/Nikolai J. Topping> <Oprettet MainMenu. Implementeret setters/getters. Implementeret updateButton clicked>
//
//========================================================================

#include "mainmenu.h"
#include "ui_mainmenu.h"

//=============================================================
// METHOD : MainMenu
// DESCR. : Constructor
//=============================================================
MainMenu::MainMenu(QStackedWidget *parent, UnitRegister &regRef, CommInterface &commRef) :
    QWidget(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    this->setAccessibleName("Main Menu");
    parentPtr = parent;
    setRegistryPtr(regRef);
    setCommPtr(commRef);
    //Fang vores unitTable så der kan skrives til den.
    setTablePtr(this->findChild<QTableWidget*>("unitTable"));
    //on_updateButton_clicked();
}

//=============================================================
// METHOD : ~MainMenu
// DESCR. : Destructor
//=============================================================
MainMenu::~MainMenu()
{
    delete ui;
}

//=============================================================
// METHOD : setTablePtr
// DESCR. : Sætter pointeren til det table der vises i UI.
//=============================================================
void MainMenu::setTablePtr(QTableWidget* tableRef) {
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

//=============================================================
// METHOD : updateFromCommandBox
// DESCR. : Opdaterer status på enheder fra styreboksen
//=============================================================
void MainMenu::updateFromCommandBox() {
    if(getRegistryPtr() != NULL)
    {
        //Lambda expression - Opdaterer status for enhederne i enhedsregistret.
        //99% magi. Source: http://stackoverflow.com/questions/37300108/iterate-through-vector-contained-in-another-class -- LOL
        getRegistryPtr()->updateStates([&](uchar ID) { return getCommPtr()->getUnitStatus(ID); });
        if(tablePtr != NULL) {
            tablePtr->setRowCount(getRegistryPtr()->getRegistrySize());
            int rowCount = 0;
            vector<Unit>::iterator iter;
            QString inf;
            for(iter = getRegistryPtr()->begin(); iter != getRegistryPtr()->end(); ++iter) {
                //Returnere unitID som uchar, caster til int. QString::number gemmer int som en QString.
                inf = QString::number(+(iter->getUnitID()));
                tablePtr->setItem( rowCount, 0, new QTableWidgetItem( inf ) );
                //Returnere RoomID som uchar, caster til int. QString::number gemmer int som en QString.
                inf = QString::number(+(iter->getRoomID()));
                tablePtr->setItem( rowCount, 1, new QTableWidgetItem( inf ) );
                if(+( iter->getStatus() ) )
                    inf = "Tændt";
                else
                    inf = "Slukket";
                tablePtr->setItem( rowCount, 2, new QTableWidgetItem( inf ) );
                rowCount += 1;
            }
        }
    }
}

//=============================================================
// METHOD : updateFromLocal
// DESCR. : Opdaterer tabellen med enheder ud fra lokal lager.
//=============================================================
void MainMenu::updateFromLocal() {
    if(getRegistryPtr() != NULL)
    {
        if(tablePtr != NULL) {
            tablePtr->setRowCount(getRegistryPtr()->getRegistrySize());
            int rowCount = 0;
            vector<Unit>::iterator iter;
            QString inf;
            for(iter = getRegistryPtr()->begin(); iter != getRegistryPtr()->end(); ++iter) {
                //Returnere unitID som uchar, caster til int. QString::number gemmer int som en QString.
                inf = QString::number(+((*iter).getUnitID()));
                tablePtr->setItem( rowCount, 0, new QTableWidgetItem( inf ) );
                //Returnere RoomID som uchar, caster til int. QString::number gemmer int som en QString.
                inf = QString::number(+((*iter).getRoomID()));
                tablePtr->setItem( rowCount, 1, new QTableWidgetItem( inf ) );
                if(+((*iter).getStatus()))
                    inf = "Tændt";
                else
                    inf = "Slukket";
                tablePtr->setItem( rowCount, 2, new QTableWidgetItem( inf ) );
                rowCount += 1;
            }
        }
    }
}

//=============================================================
// METHOD : on_updateButton_clicked
// DESCR. : Slot der kaldes ved tryk på "Opdater Enhedsstatus"
//=============================================================
void MainMenu::on_updateButton_clicked()
{
    updateFromCommandBox();
}

//=============================================================
// METHOD : on_addUnit_PushButton_clicked
// DESCR. : Slot der kaldes når der trykkes på knappen "Tilføj Enhed"
//=============================================================
void MainMenu::on_addUnit_PushButton_clicked()
{
    for(int i = 0; i < getParentPtr()->count(); ++i) {
        if(getParentPtr()->widget(i)->accessibleName().compare("Add Unit") == 0) {
            getParentPtr()->setCurrentIndex(i);
            return;
        }
    }
    cerr << "Kan ikke finde Add Unit" << endl;
}

//=============================================================
// METHOD : on_remUnit_PushButton_clicked
// DESCR. : Slot der kaldes når der trykkes på "Fjern enhed"
//=============================================================
void MainMenu::on_remUnit_PushButton_clicked()
{
    for(int i = 0; i < getParentPtr()->count(); ++i) {
        if(getParentPtr()->widget(i)->accessibleName().compare("Remove Unit") == 0) {
            getParentPtr()->setCurrentIndex(i);
            return;
        }
    }
    cerr<< "Kan ikke finde Remove Unit" << endl;
    //getParentPtr()->setCurrentIndex(2);
}

//=============================================================
// METHOD : on_editUnit_PushButton_clicked
// DESCR. : Slot der kaldes når der trykkes på "Ret Enhed"
//=============================================================
void MainMenu::on_editUnit_PushButton_clicked()
{
    for(int i = 0; i < getParentPtr()->count(); ++i) {
        if(getParentPtr()->widget(i)->accessibleName().compare("Edit Unit") == 0) {
            getParentPtr()->setCurrentIndex(i);
            return;
        }
    }
    cerr << "Kan ikke finde Edit Unit" << endl;
}

//=============================================================
// METHOD : on_TimeSchuduleButtin_clicked
// DESCR. : Slot der kaldes når der trykkes på "Tidsplaner"
//=============================================================
void MainMenu::on_TimeSchuduleButtin_clicked()
{
    for(int i = 0; i < getParentPtr()->count(); ++i) {
        if(getParentPtr()->widget(i)->accessibleName().compare("Edit Entry") == 0) {
            getParentPtr()->setCurrentIndex(i);
            return;
        }
    }
    cerr<< "Kan ikke finde Edit Entry" << endl;
}
