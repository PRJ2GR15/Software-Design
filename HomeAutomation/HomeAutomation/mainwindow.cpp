#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, UnitRegister& regRef, CommInterface& commRef) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setRegistryPtr(regRef);
    setCommPtr(commRef);
    mainMenuPtr = new MainMenu(ui->MainW_StackedWidget, regRef, commRef);
    removeUnitPtr = new RemoveUnit(ui->MainW_StackedWidget, regRef, commRef);
    addUnitPtr = new AddUnit(ui->MainW_StackedWidget, regRef, commRef);
    //mainMenuPtr->setCommPtr(*commPtr);

    ui->MainW_StackedWidget->addWidget(mainMenuPtr);
    ui->MainW_StackedWidget->addWidget(removeUnitPtr);
    ui->MainW_StackedWidget->addWidget(addUnitPtr);
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
