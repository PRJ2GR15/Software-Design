//========================================================================
// FILENAME : <MainMenu.h>
// CREATED : <18/05-2016>
// AUTHOR : <Nikolai James Topping>
// DESCR. : <Header filen for MainMenu>
//
//------------------------------------------------------------------------
//
// REV. DATE/AUTHOR CHANGE DESCRIPTION
// 1.0 <18-05/2016/Nikolai J. Topping> <Oprettet fil. Oprettet setters/getters. Oprettet updateButton slot for clicked>
// 1.1 <20-05/2016/Nikolai J. Topping> <Oprettet metoder for addunit og remove unit knapperne>
//========================================================================

#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include "basemenu.h"

namespace Ui {
class MainMenu;
}

class MainMenu : public QWidget, public BaseMenu
{
    const int invalidSelection;
    Q_OBJECT

public:
    MainMenu(QStackedWidget *parent, UnitRegister& regRef, CommInterface& commRef);
    ~MainMenu();

    QTableWidget* getTablePtr() { return tablePtr; }

    void setTablePtr(QTableWidget* tableRef);

    void updateFromCommandBox();

    void updateFromLocal();

private slots:
    void on_updateButton_clicked();

    void on_unitTable_cellClicked(int row, int column);

    void on_addUnit_PushButton_clicked();

    void on_remUnit_PushButton_clicked();

    void on_pushButton_2_clicked();

    void on_editUnit_PushButton_clicked();

private:
    Ui::MainMenu *ui;
    QTableWidget* tablePtr;
    int selectedRow;
};

#endif // MAINMENU_H
