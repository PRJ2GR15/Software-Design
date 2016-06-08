//========================================================================
// FILENAME : <UnitRegister.cpp>
// CREATED : <17/05-2016>
// AUTHOR : <Nikolai James Topping>
// DESCR. : <Implementering af UnitRegister>
//
//------------------------------------------------------------------------
//
// REV. DATE/AUTHOR CHANGE DESCRIPTION
// 1.0 <18.05/2016/Nikolai J. Topping> <Tilføjet data fra QT projekt>
// 1.1 <21/05-2016/Anders Brondbjerg Knudsen <Tilføjet addNewTime og upDate time>
//========================================================================
#include "UnitRegister.h"

//=============================================================
// METHOD : 
// DESCR. : 
//=============================================================

UnitRegister::UnitRegister()
{
	
}



//=============================================================
// METHOD : 
// DESCR. : 
//=============================================================

bool UnitRegister::storeUnit(Unit& unitRef)
{
    if ( !compareID(unitRef.getUnitID()) )
	{
		unitRegister_.push_back(unitRef);
        return true;
	}
    else
    {
        return false;
    }
}

//=============================================================
// METHOD : 
// DESCR. : 
//=============================================================

bool UnitRegister::compareID(uchar unitID) const
{
	vector<Unit>::const_iterator iter;
	for (iter = unitRegister_.begin(); iter != unitRegister_.end(); ++iter)
	{
		if (unitID == (*iter).getUnitID())
			return true; //ID Findes allerede
	}
	return false; //ID Findes ikke

}

//=============================================================
// METHOD : 
// DESCR. : 
//=============================================================

bool UnitRegister::updateStatus(uchar unitID, bool status)
{
	vector<Unit>::iterator iter;
	for (iter = unitRegister_.begin(); iter != unitRegister_.end(); ++iter)
	{
		if (unitID == (*iter).getUnitID())
		{
			(*iter).setStatus(status);
			return true;
		}
	}
	return false;
}



//=============================================================
// METHOD : 
// DESCR. : 
//=============================================================

bool UnitRegister::deleteUnit(uchar unitID)
{
	vector<Unit>::iterator iter;
	for (iter = unitRegister_.begin(); iter != unitRegister_.end(); ++iter)
	{
		if (unitID == (*iter).getUnitID())
		{
			unitRegister_.erase(iter);
			return true;
		}
	}
	return false;
}

//=============================================================
// METHOD : 
// DESCR. : 
//=============================================================

bool UnitRegister::modifyUnit(uchar originalUnitID, uchar unitID, uchar roomID)
{
    vector<Unit>::iterator iter;
    for(iter = unitRegister_.begin(); iter != unitRegister_.end(); ++iter)
    {
        if(originalUnitID == iter->getUnitID())
        {
            iter->setUnitID(unitID);
            iter->setRoomID(roomID);
            return true;
        }
    }
    return false;
}



//=============================================================
// METHOD : 
// DESCR. : 
//=============================================================

UnitRegister::~UnitRegister()
{
}
