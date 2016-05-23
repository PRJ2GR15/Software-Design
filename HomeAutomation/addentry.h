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

public slots:
void getUnit(int id);


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::AddEntry *ui;
    int unitID;
};

#endif // ADDENTRY_H
