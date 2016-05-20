#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mainMenuPtr = new MainMenu(ui->MainW_StackedWidget);
    removeUnitPtr = new RemoveUnit(ui->MainW_StackedWidget);
    mainMenuPtr->setCommPtr(*commPtr);

    ui->MainW_StackedWidget->addWidget(mainMenuPtr);
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
        mainMenuPtr->setRegistryPtr(regRef);
        registryPtr = &regRef;
    }
    else
        cerr << "Couldn't register unit registry address" << endl;
}

void MainWindow::setCommPtr(CommInterface& commRef) {
    if(&commRef != NULL) {
        commPtr = &commRef;
        mainMenuPtr->setCommPtr(commRef);
    }
    else
        cerr << "Couldn't register comm interface address" << endl;
}
