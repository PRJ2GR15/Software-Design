//========================================================================
// FILENAME : <BaseMenu.cpp>
// CREATED : <19/05-2016>
// AUTHOR : <Nikolai J. Topping>
// DESCR. : <Implementering af basemenu. Bruges som basisklasse for andre menuer.>
//
//------------------------------------------------------------------------
//
// REV. DATE/AUTHOR CHANGE DESCRIPTION
// 1.0 <20-05/2016/Anders Brondbjerg Knudsen> <Oprettelse af addUnit>
//========================================================================
#include "basemenu.h"

//=============================================================
// METHOD : default constructor
// DESCR. :
//=============================================================

BaseMenu::BaseMenu()
{

}

//=============================================================
// METHOD : setRegistryPtr(UnitRegister& regRef)
// DESCR. : Funktionen sætter en pointer til klassen UnitRegister
//=============================================================
void BaseMenu::setRegistryPtr(UnitRegister& regRef) {
    //TODO - Validering
    if(&regRef != NULL)
        registryPtr = &regRef;
    else
        cerr << "Couldn't register unit registry address" << endl;
}

//=============================================================
// METHOD : setCommPtr(CommInterface& commRef)
// DESCR. : Funktionen sætter en pointer til klassen commInterface
//=============================================================
void BaseMenu::setCommPtr(CommInterface& commRef) {
    if(&commRef != NULL) {
        commPtr = &commRef;
    }
    else
        cerr << "Couldn't register comm interface address" << endl;
}

