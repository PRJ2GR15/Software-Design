#ifndef EDITOLDENTRY_H
#define EDITOLDENTRY_H

#include <QWidget>
#include "basemenu.h"

namespace Ui {
class EditOldEntry;
}

class EditOldEntry : public QWidget, public BaseMenu
{
    Q_OBJECT

public:
    EditOldEntry(QStackedWidget *parent, UnitRegister& regRef, CommInterface& commRef);
    ~EditOldEntry();
    void setTablePtr(QTableWidget* tableRef);
    void populateTable();
public slots:
void getUnit(int id);

private slots:

void on_EditEntryTable_cellClicked(int row, int column);

void on_Annuller_clicked();

void on_SaveEntry_clicked();

private:
    Ui::EditOldEntry *ui;
    QTableWidget* tablePtr;
    int unitID;
    map<unsigned char, int> myMap;
    int entryID;
    int selectedRow=-1;
};

#endif // EDITOLDENTRY_H
