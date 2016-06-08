#ifndef EDITENTRY_H
#define EDITENTRY_H

#include <QWidget>
#include "basemenu.h"

namespace Ui {
class EditEntry;
}

class EditEntry : public QWidget, public BaseMenu
{
    Q_OBJECT

public:
    EditEntry(QStackedWidget *parent, UnitRegister& regRef, CommInterface& commRef);
    ~EditEntry();
    void setTablePtr(QTableWidget* tableRef);
    void populateTable();
    void returnSelected();
    int selectedRow= -1;

signals:
    void sendid(int);

private slots:

    void on_EntryTable_cellClicked(int row, int column);



    void on_RemoveEntry_clicked();
    void on_AddEntry_clicked();

    void on_ScheduleCancel_clicked();

    void on_EditSchedule_clicked();

protected:
    //int selectedRow= -1;
private:
    Ui::EditEntry *ui;
    QTableWidget* tablePtr;
    int selectedCol=0;
};

#endif // EDITENTRY_H
