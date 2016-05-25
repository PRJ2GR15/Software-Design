#ifndef REMOVEENTRY_H
#define REMOVEENTRY_H

#include <QWidget>
#include "basemenu.h"

namespace Ui {
class RemoveEntry;
}

class RemoveEntry : public QWidget, public BaseMenu
{
    Q_OBJECT

public:
    RemoveEntry(QStackedWidget *parent, UnitRegister& regRef, CommInterface& commRef);
    ~RemoveEntry();

    void setTablePtr(QTableWidget* tableRef);
    void populateTable();

public slots:
void getUnit(int id);

private slots:
void on_RemoveEntry_2_clicked();

void on_EntriesTable_cellClicked(int row, int column);

void on_Annuller_clicked();

void on_RemoveEntriesForDay_clicked();

private:
    Ui::RemoveEntry *ui;
    map<unsigned char, int> myMap;
    int unitID;
    QTableWidget* tablePtr;
    int entryID;
    int selectedRow=-1;
};

#endif // REMOVEENTRY_H
