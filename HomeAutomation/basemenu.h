//========================================================================
// FILENAME : <BaseMenu.h>
// CREATED : <19/05-2016>
// AUTHOR : <Nikolai James Topping>
// DESCR. : <Bruges som basis-klasse for alle undermenuer.>
//
//------------------------------------------------------------------------
//
// REV. DATE/AUTHOR CHANGE DESCRIPTION
// 1.0 <19-05/2016/Nikolai J. Topping> <Oprettet fil. Tilføjet set/get metoder samt private/protected variabler.>
//========================================================================
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
