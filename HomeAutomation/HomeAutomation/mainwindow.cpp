//========================================================================
// FILENAME : <MainWindow.cpp>
// CREATED : <17/05-2016>
// AUTHOR : <Nikolai James Topping>
// DESCR. : <Implementering af MainWindow>
//
//------------------------------------------------------------------------
//
// REV. DATE/AUTHOR CHANGE DESCRIPTION
// 1.0 <17.05/2016/Nikolai J. Topping> <Oprettet MainWindow>
// 1.1 <17.05/2016/Nikolai J. Topping> <Tilføjet AddUnit og RemoveUnit vinduer til StackedWidget>
// 1.2 <21.05/2016/Nikolai J. Topping> <Opdateret måden hvorpå man skifter mellem vinduer>
//
//========================================================================

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(UnitRegister& regRef, CommInterface& commRef, QWidget *parent = 0) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setRegistryPtr(regRef);
    setCommPtr(commRef);
    mainMenuPtr = new MainMenu(ui->MainW_StackedWidget, regRef, commRef);
    removeUnitPtr = new RemoveUnit(ui->MainW_StackedWidget, regRef, commRef);
    addUnitPtr = new AddUnit(ui->MainW_StackedWidget, regRef, commRef);

    ui->MainW_StackedWidget->addWidget(mainMenuPtr);
    ui->MainW_StackedWidget->addWidget(addUnitPtr);
    ui->MainW_StackedWidget->addWidget(removeUnitPtr);
    ui->MainW_StackedWidget->setCurrentWidget(mainMenuPtr);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setRegistryPtr(UnitRegister& regRef) {
    //TODO - Validering
    if(&regRef != NULL) {
        registryPtr = &regRef;
    }
    else
        cerr << "Couldn't register unit registry address" << endl;
}

void MainWindow::setCommPtr(CommInterface& commRef) {
    if(&commRef != NULL) {
        commPtr = &commRef;
    }
    else
        cerr << "Couldn't register comm interface address" << endl;
}

void MainWindow::on_MainW_StackedWidget_currentChanged(int arg1)
{
    QString tmpString = QString(ui->MainW_StackedWidget->currentWidget()->accessibleName());
    if(tmpString.compare("Main Menu") == 0) {
        mainMenuPtr->updateFromLocal();
    } else if(tmpString.compare("Remove Unit") == 0) {
        removeUnitPtr->populateTable();
    } else {
        cout << "Default" << endl;
    }
}
