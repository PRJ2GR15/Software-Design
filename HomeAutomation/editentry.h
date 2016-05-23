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

signals:
    void sendid(int);

private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_EntryTable_cellClicked(int row, int column);

private:
    Ui::EditEntry *ui;
    QTableWidget* tablePtr;
    int selectedRow= -1;
};

#endif // EDITENTRY_H
