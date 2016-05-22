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


private slots:
    void on_pushButton_clicked();

private:
    Ui::EditEntry *ui;
    QTableWidget* tablePtr;
};

#endif // EDITENTRY_H
