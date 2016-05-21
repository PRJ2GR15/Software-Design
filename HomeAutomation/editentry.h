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
    EditEntry(QWidget *parent, UnitRegister& regRef, CommInterface& commRef);
    ~EditEntry();

private:
    Ui::EditEntry *ui;
};

#endif // EDITENTRY_H
