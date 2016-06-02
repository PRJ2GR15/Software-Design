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
	//outputFile = "./register.txt";
    //loadData();
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

bool UnitRegister::AddNewtime(uchar unitID,int day, Entry &obj)
{
    vector<Unit>::iterator iter;
    for(iter=unitRegister_.begin();iter!=unitRegister_.end();++iter)
        if(iter->getUnitID()==unitID)
    {
            if(iter->storeEntry(day,obj)==false)
                return false;
    }
    return true;
}



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

/*bool UnitRegister::updateTime(uchar roomID, int placeholder)
{
}*/

//=============================================================
// METHOD : 
// DESCR. : 
//=============================================================

bool UnitRegister::updateTime(uchar unitID,int day, int placeholder, uchar hour, uchar min)
{
    vector<Unit>::iterator iter;
    for(iter=unitRegister_.begin();iter!=unitRegister_.end();++iter)
        if(iter->getUnitID()==unitID)
    {
            if(iter->updateEntry(day,placeholder,hour,min)==false)
                return false;
    }
    return true;
}

//=============================================================
// METHOD : 
// DESCR. : 
//=============================================================

UnitRegister::~UnitRegister()
{
}
