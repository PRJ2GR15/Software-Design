#ifndef ADDUNIT_H
#define ADDUNIT_H

#include <QWidget>
#include "basemenu.h"

namespace Ui {
class AddUnit;
}

class AddUnit : public QWidget, public BaseMenu
{
    Q_OBJECT

public:
    explicit AddUnit(QStackedWidget *parent = 0, UnitRegister& regRef, CommInterface& commRef);
    ~AddUnit();

private:
    Ui::AddUnit *ui;
};

#endif // ADDUNIT_H
