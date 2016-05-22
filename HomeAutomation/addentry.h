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

private slots:
    void on_pushButton_clicked();

private:
    Ui::AddEntry *ui;
};

#endif // ADDENTRY_H
