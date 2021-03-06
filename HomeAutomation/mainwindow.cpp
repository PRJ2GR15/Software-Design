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

//=============================================================
// METHOD : MainWindow
// DESCR. : Constructor
//=============================================================
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
    editPtr = new EditEntry(ui->MainW_StackedWidget, regRef, commRef);
    editUnitPtr = new EditUnit(ui->MainW_StackedWidget, regRef, commRef);
    addEntryPtr = new AddEntry(ui->MainW_StackedWidget, regRef, commRef);
    editEntryPtr = new EditOldEntry(ui->MainW_StackedWidget, regRef, commRef);
    removeEntryPtr = new RemoveEntry(ui->MainW_StackedWidget, regRef, commRef);
    waitPtr = new waitForPin(ui->MainW_StackedWidget, commRef);


    ui->MainW_StackedWidget->addWidget(mainMenuPtr);
    ui->MainW_StackedWidget->addWidget(addUnitPtr);
    ui->MainW_StackedWidget->addWidget(editUnitPtr);
    ui->MainW_StackedWidget->addWidget(editPtr);
    ui->MainW_StackedWidget->addWidget(addEntryPtr);
    ui->MainW_StackedWidget->addWidget(editEntryPtr);
    ui->MainW_StackedWidget->addWidget(removeUnitPtr);
    ui->MainW_StackedWidget->addWidget(removeEntryPtr);
    ui->MainW_StackedWidget->addWidget(waitPtr);

    ui->MainW_StackedWidget->setCurrentWidget(mainMenuPtr);

    QObject::connect(editPtr,SIGNAL(sendid(int)),
                     addEntryPtr,SLOT(getUnit(int)));

    QObject::connect(editPtr,SIGNAL(sendid(int)),
                        editEntryPtr,SLOT(getUnit(int)));

    QObject::connect(editPtr,SIGNAL(sendid(int)),
                     removeEntryPtr,SLOT(getUnit(int)));
}

//=============================================================
// METHOD : ~MainWindow
// DESCR. : Destructor
//=============================================================
MainWindow::~MainWindow()
{
    //commPtr->PCDisconnected();
    commPtr->closeComPort();
    delete ui;
}

//=============================================================
// METHOD : setRegistryPtr
// DESCR. : Sætter pointeren til UnitRegister
//=============================================================
void MainWindow::setRegistryPtr(UnitRegister& regRef) {
    //TODO - Validering
    if(&regRef != NULL) {
        registryPtr = &regRef;
    }
    else
        cerr << "Couldn't register unit registry address" << endl;
}

//=============================================================
// METHOD : setCommPtr
// DESCR. : Sætter pointeren til CommInterface
//=============================================================
void MainWindow::setCommPtr(CommInterface& commRef) {
    if(&commRef != NULL) {
        commPtr = &commRef;
    }
    else
        cerr << "Couldn't register comm interface address" << endl;
}

//=============================================================
// METHOD : on_MainW_StackedWidget_currentChanged
// DESCR. : Slot der kaldes hver gang der skiftes aktiv widget i QStackedWidget
//=============================================================
void MainWindow::on_MainW_StackedWidget_currentChanged(int arg1)
{
    QString tmpString = QString(ui->MainW_StackedWidget->currentWidget()->accessibleName());
    if(tmpString.compare("Main Menu") == 0) {
        mainMenuPtr->updateFromLocal();
    } else if(tmpString.compare("Remove Unit") == 0) {
        removeUnitPtr->populateTable();
        removeUnitPtr->selectedRow = -1;
    } else if(tmpString.compare("Edit Unit") == 0) {
        editUnitPtr->updateTable();
    }
    else if(tmpString.compare("Edit Entry") == 0) {
            editPtr->populateTable();
            editPtr->selectedRow = -1;
    }
    else if(tmpString.compare("Add Entry") == 0) {
            addEntryPtr->populateTable();
    }
    else if(tmpString.compare("Edit Old Entry") == 0)
       {      editEntryPtr->populateTable();
       }

    else if(tmpString.compare("Remove Entry") == 0)
       {      removeEntryPtr->populateTable();
       }
}
