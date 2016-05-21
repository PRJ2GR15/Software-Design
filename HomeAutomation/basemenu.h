#ifndef BASEMENU_H
#define BASEMENU_H

#include "UnitRegister.h"
#include "CommInterface.h"
#include <QtWidgets>

class BaseMenu
{
public:
    void setRegistryPtr(UnitRegister& regRef);

    void setCommPtr(CommInterface& commRef);

    UnitRegister* getRegistryPtr() { return registryPtr; }

    CommInterface* getCommPtr() { return commPtr; }

    QStackedWidget* getParentPtr() { return parentPtr; }

protected:
    BaseMenu();
    QStackedWidget* parentPtr;
private:
    UnitRegister* registryPtr;
    CommInterface* commPtr;


};

#endif // BASEMENU_H
