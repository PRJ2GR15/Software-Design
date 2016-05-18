#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    QFile file("C:\\Users\\Yeezy\\Documents\\GitHub\\Software-Design\\HomeAutomation\\HomeAutomation\\register.txt");

    if(!file.open(QIODevice::ReadOnly))
        QMessageBox::information(0,"Info",file.errorString());


    QTextStream in(&file);

    ui->textBrowser->setText(in.readAll());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{

}

void MainWindow::on_OpdaterStatus_clicked()
{

}
