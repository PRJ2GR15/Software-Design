#ifndef ADDENTRY_H
#define ADDENTRY_H

#include <QWidget>
#include "basemenu.h"

namespace Ui {
class AddEntry;
}

class AddEntry : public QWidget, public BaseMenu
{
    Q_OBJECT

public:
    AddEntry(QStackedWidget *parent, UnitRegister& regRef, CommInterface& commRef);
    ~AddEntry();
    void setTablePtr(QTableWidget* tableRef);
    void populateTable();

public slots:
void getUnit(int id);


private slots:


    void on_Cancel_clicked();


    void on_AddTheEntry_clicked();

private:
    Ui::AddEntry *ui;
    QTableWidget* tablePtr;
    int unitID;
};

#endif // ADDENTRY_H
