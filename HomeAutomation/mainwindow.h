#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//========================================================================
// FILENAME : <MainWindow.h>
// CREATED : <18/05-2016>
// AUTHOR : <Nikolai James Topping>
// DESCR. : <Header filen for MainWindow>
//
//------------------------------------------------------------------------
//
// REV. DATE/AUTHOR CHANGE DESCRIPTION
// 1.0 <18-05/2016/Nikolai J. Topping> <Oprettet fil. Oprettet setters/getters. UnitRegister og MainMenu pointers.>
// 1.1 <20-05/2016/Nikolai J. Topping> <Tilføjet RemoveUnit/AddUnit.>
// 1.2 <20-05/2016/Nikolai J. Topping> <Tilføjet "CurrentChanged" slot funktion til stacked widget>
// 1.3 <21-05/2016/Nikolai J. Topping> <Tilføjet EditUnit/EditEntry>
//========================================================================


#include <QMainWindow>
#include <QtWidgets>
#include "basemenu.h"
#include "mainmenu.h"
#include "removeunit.h"
#include "addunit.h"
#include "editentry.h"
#include "editunit.h"
#include "addentry.h"
#include "editoldentry.h"
#include "removeentry.h"
#include "waitforpin.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(UnitRegister& regRef, CommInterface& commRef, QWidget *parent);
    ~MainWindow();

    void setRegistryPtr(UnitRegister& regRef);

    void setTablePtr(QTableWidget* tableRef);

    void setCommPtr(CommInterface& commRef);

    QTableWidget* getTablePtr() { return tablePtr; }

    UnitRegister* getRegistryPtr() { return registryPtr; }

    CommInterface* getCommPtr() { return commPtr; }

private slots:
    void on_MainW_StackedWidget_currentChanged(int arg1);

private:

    Ui::MainWindow *ui;
    MainMenu* mainMenuPtr;
    RemoveUnit* removeUnitPtr;
    AddUnit* addUnitPtr;
    UnitRegister* registryPtr;
    CommInterface* commPtr;
    QTableWidget* tablePtr;
    EditEntry* editPtr;
    EditUnit* editUnitPtr;
    AddEntry* addEntryPtr;
    EditOldEntry* editEntryPtr;
    RemoveEntry* removeEntryPtr;
    waitForPin* waitPtr;
};

#endif // MAINWINDOW_H
