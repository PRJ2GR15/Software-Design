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
// METHOD :
// DESCR. :
//=============================================================
MainMenu::MainMenu(QStackedWidget *parent, UnitRegister &regRef, CommInterface &commRef) :
    QWidget(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    parentPtr = parent;
    setRegistryPtr(regReg);
    //Fang vores unitTable så der kan skrives til den.
    setTablePtr(this->findChild<QTableWidget*>("unitTable"));
}

//=============================================================
// METHOD :
// DESCR. :
//=============================================================
MainMenu::~MainMenu()
{
    delete ui;
}

//=============================================================
// METHOD :
// DESCR. :
//=============================================================
void MainMenu::setTablePtr(QTableWidget* tableRef) {
    if(tableRef != NULL) {
        tablePtr = tableRef;
        //Sørger for at man ikke kan redigere i vores table.
        tablePtr->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }
    else
        cerr << "Couldn't register table address" << endl;
}


//=============================================================
// METHOD :
// DESCR. :
//=============================================================
void MainMenu::on_updateButton_clicked()
{
    if(getRegistryPtr() != NULL)
        //Lambda expression - Opdaterer status for enhederne i enhedsregistret.
        //99% magi. Source: http://stackoverflow.com/questions/37300108/iterate-through-vector-contained-in-another-class
        getRegistryPtr()->updateStates([&](uchar ID) { return getCommPtr()->getUnitStatus(ID); });

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

void MainMenu::on_pushButton_3_clicked()
{
    getParentPtr()->setCurrentIndex(1);
}



void MainMenu::on_unitTable_cellClicked(int row, int column)
{
    cout << "Cell in row: " << row << ", column: " << column << " clicked." << endl;
}
