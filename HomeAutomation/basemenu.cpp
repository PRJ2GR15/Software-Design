#include "basemenu.h"

BaseMenu::BaseMenu()
{

}

//=============================================================
// METHOD :
// DESCR. :
//=============================================================
void BaseMenu::setRegistryPtr(UnitRegister& regRef) {
    //TODO - Validering
    if(&regRef != NULL)
        registryPtr = &regRef;
    else
        cerr << "Couldn't register unit registry address" << endl;
}

//=============================================================
// METHOD :
// DESCR. :
//=============================================================
void BaseMenu::setCommPtr(CommInterface& commRef) {
    if(&commRef != NULL) {
        commPtr = &commRef;
    }
    else
        cerr << "Couldn't register comm interface address" << endl;
}

