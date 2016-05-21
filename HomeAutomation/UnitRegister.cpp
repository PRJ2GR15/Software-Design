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
//
//========================================================================
#include "UnitRegister.h"

//=============================================================
// METHOD : 
// DESCR. : 
//=============================================================

UnitRegister::UnitRegister()
{
	//outputFile = "./register.txt";
	loadData();
}

//=============================================================
// METHOD : 
// DESCR. : 
//=============================================================

bool UnitRegister::loadData()
{
	int u = 0x00; int r = 0x00; bool s = false; int t = 0;
	//TODO - Validering, så den rent faktisk åbner den rigtige fil, det rigtige sted
    string path = "register.txt";
    in.open(path,ios::in);
    if (!in)
	{
		cerr << "Filen findes ikke" << endl;
		return false;
	}
		
    while (!in.eof())
	{
		in >> u >> r >> s >> t;
        if (!compareID(u)) {
            unitRegister_.push_back(Unit(static_cast<uchar>(u), static_cast<uchar>(r), s, t));
        }
		else
			cout << "Unit already exists" << endl;
	}
	in.close();
	return true;
}

//=============================================================
// METHOD : 
// DESCR. : 
//=============================================================

bool UnitRegister::storeUnit(Unit& unitRef)
{
	if (!compareID(unitRef.getUnitID()))
	{
		unitRegister_.push_back(unitRef);
        return true;
	}
    else
    {
        vector<Unit>::iterator iter;
        for(iter = unitRegister_.begin(); iter != unitRegister_.end(); ++iter) {
            if(iter->getUnitID() == unitRef.getUnitID())
                *iter = unitRef;
        }
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

void UnitRegister::getStoredUnits()
{
	vector<Unit>::iterator iter;
	for (iter = unitRegister_.begin(); iter != unitRegister_.end(); ++iter)
        iter->printEntry();
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

bool UnitRegister::modifyUnit(uchar unitID, uchar roomID)
{
	return true;
}

/*bool UnitRegister::updateTime(uchar roomID, int placeholder)
{
}*/

//=============================================================
// METHOD : 
// DESCR. : 
//=============================================================

bool UnitRegister::updateTime(uchar unitID, int placeholder)
{
	return true;
}

//=============================================================
// METHOD : 
// DESCR. : 
//=============================================================

UnitRegister::~UnitRegister()
{
}
