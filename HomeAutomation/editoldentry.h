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

private:
    Ui::EditOldEntry *ui;
};

#endif // EDITOLDENTRY_H
