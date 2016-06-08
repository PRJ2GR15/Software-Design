#ifndef ADDUNIT_H
#define ADDUNIT_H

#include <QWidget>
#include "basemenu.h"

//========================================================================
// FILENAME : <addUnit.h>
// CREATED : <20/05-2016>
// AUTHOR : <Anders Brondbjerg Knudsen>
// DESCR. : <Header filen for addUnit>
//
//------------------------------------------------------------------------
//
// REV. DATE/AUTHOR CHANGE DESCRIPTION
// 1.0 <20-05/2016/Anders Brondbjerg Knudsen> <Oprettelse af addUnit>
//========================================================================

namespace Ui {
class AddUnit;
}

class AddUnit : public QWidget, public BaseMenu
{
    Q_OBJECT

public:
    AddUnit(QStackedWidget *parent, UnitRegister& regRef, CommInterface& commRef);
    ~AddUnit();

private slots:

    void on_AddUnit_2_clicked();

    void on_Cancel_clicked();

private:
    Ui::AddUnit *ui;
};

#endif // ADDUNIT_H
