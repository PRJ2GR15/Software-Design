#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "EnhedsRegister.h"
#include "CommInterface.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setRegistryPtr(EnhedsRegister& regRef) {
        //TODO - Validering
        if(&regRef != NULL)
            registryPtr = &regRef;
        else
            cerr << "Couldn't register unit registry address" << endl;
    }

    void setTablePtr(QTableWidget* tableRef) {
        if(tableRef != NULL) {
           tablePtr = tableRef;
           tablePtr->setEditTriggers(QAbstractItemView::NoEditTriggers);
        }
        else
            cerr << "Couldn't register table address" << endl;
    }

    void setCommPtr(CommInterface& commRef) {
        if(&commRef != NULL) {
            commPtr = &commRef;
        }
        else
            cerr << "Couldn't register comm interface address" << endl;
    }

    QTableWidget* getTablePtr() {
        return tablePtr;
    }

    EnhedsRegister* getRegistryPtr() {
        return registryPtr;
    }

    CommInterface* getCommPtr() {
        return commPtr;
    }

private slots:
    void on_opdaterStatus_clicked();

private:
    Ui::MainWindow *ui;
    EnhedsRegister* registryPtr;
    QTableWidget* tablePtr;
    CommInterface* commPtr;

};

#endif // MAINWINDOW_H
