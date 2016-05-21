#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "mainmenu.h"
#include "removeunit.h"
#include "addunit.h"
#include "CommInterface.h"
#include "UnitRegister.h"
#include "editentry.h"

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
};

#endif // MAINWINDOW_H
