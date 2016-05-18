//========================================================================
// FILENAME : <EnhedsRegister.cpp>
// CREATED : <17/05-2016>
// AUTHOR : <Author>
// DESCR. : <Description of file contents>
//
//------------------------------------------------------------------------
//
// REV. DATE/AUTHOR CHANGE DESCRIPTION
// 1.0 <rev. date/author> <Change description>
//========================================================================


#include "EnhedsRegister.h"

//=============================================================
// METHOD : 
// DESCR. : 
//=============================================================

EnhedsRegister::EnhedsRegister()
{
	outputFile = "./register.txt";
	loadData();
}

//=============================================================
// METHOD : 
// DESCR. : 
//=============================================================


bool EnhedsRegister::loadData()
{
	int u = 0x00; int r = 0x00; bool s = false; int t = 0;
	in.open(outputFile, ios::in);
	if (!in)
	{
		cerr << "Filen findes ikke" << endl;
		return false;
	}
		
	while (!in.eof())
	{
		in >> u >> r >> s >> t;
		if (!compareID(u))
			unitRegister_.push_back(unit(static_cast<char>(u), static_cast<char>(r), s, t));
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

bool EnhedsRegister::storeUnit(unit& unitRef)
{
	if (!compareID(unitRef.getUnitID()))
	{
		out.open(outputFile, ios::app);
		if (!out.is_open())
		{
			cout << "Failed to open file for STOREUNIT" << endl;
			return false;
		}
		unitRegister_.push_back(unitRef);
		out << unitRef << endl;
		out.close();
		return true;
	}
	else
	{
		cout << "Unit ID already exists" << endl;
		return false;
	}
}

//=============================================================
// METHOD : 
// DESCR. : 
//=============================================================

bool EnhedsRegister::compareID(char unitID) const
{
	vector<unit>::const_iterator iter;
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

bool EnhedsRegister::updateStatus(char unitID, bool status)
{
	vector<unit>::iterator iter;
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

void EnhedsRegister::getStoredUnits()
{
	vector<unit>::iterator iter;
	for (iter = unitRegister_.begin(); iter != unitRegister_.end(); ++iter)
		cout << *iter << endl;
}

//=============================================================
// METHOD : 
// DESCR. : 
//=============================================================

bool EnhedsRegister::deleteUnit(char unitID)
{
	vector<unit>::iterator iter;
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

bool EnhedsRegister::modifyUnit(char unitID, char roomID)
{
	return true;
}

/*bool EnhedsRegister::updateTime(char roomID, int placeholder)
{
}*/

//=============================================================
// METHOD : 
// DESCR. : 
//=============================================================

bool EnhedsRegister::updateTime(char roomID, int placeholder)
{
	return true;
}

//=============================================================
// METHOD : 
// DESCR. : 
//=============================================================

EnhedsRegister::~EnhedsRegister()
{
}