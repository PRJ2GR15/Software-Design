#include "EnhedsRegister.h"

EnhedsRegister::EnhedsRegister()
{
	outputFile = "./register.txt";
	//loadData();
}

bool EnhedsRegister::loadData()
{
	unit tmpUnit();
	in.open(outputFile);
	if(in.is_open())
	{
/*		while(!in.eof())
		{
			in >> unit[]
		}*/
		in.close();
		return true;
	}
	return false;
}


bool EnhedsRegister::storeUnit(unit& unitRef)
{
	if (!compareID(unitRef.getUnitID()))
	{
		out.open(outputFile, ios::app);
		if (!out.is_open())
			return false;
		unitRegister_.push_back(unitRef);
		out << unitRef << endl;
		out.close();
		return true;
	}
	else
	{
		return false;
	}
}

bool EnhedsRegister::compareID(char unitID) const
{
	vector<unit>::const_iterator iter;
	for (iter = unitRegister_.begin(); iter != unitRegister_.end(); ++iter)
	{
		if (unitID == (*iter).getUnitID())
			return true;
	}
	return false;

}

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



void EnhedsRegister::getStoredUnits()
{
	vector<unit>::iterator iter;
	for (iter = unitRegister_.begin(); iter != unitRegister_.end(); ++iter)
		cout << *iter << endl;
}

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

bool EnhedsRegister::modifyUnit(char unitID, char roomID)
{
	return true;
}

/*bool EnhedsRegister::updateTime(char roomID, int placeholder)
{
}*/

bool EnhedsRegister::updateTime(char roomID, int placeholder)
{
	return true;
}

EnhedsRegister::~EnhedsRegister()
{
}
