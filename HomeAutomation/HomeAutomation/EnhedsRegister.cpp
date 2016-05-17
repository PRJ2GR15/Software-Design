#include "EnhedsRegister.h"

EnhedsRegister::EnhedsRegister()
{
	outputFile = "./register.txt";
	loadData();
}

bool EnhedsRegister::loadData()
{
	//unit tmpUnit(0x00, 0x00, false, 0);
	int u = 0x00; int r = 0x00; bool s = false; int t = 0;
	//in.open(outputFile, ios::in);
	ifstream inFile("register.txt", ios::in);
	if (!inFile)
	{
		cerr << "Filen findes ikke" << endl;
		return false;
	}
		
	while (!inFile.eof())
	{
		inFile >> u >> r >> s >> t;
		unitRegister_.push_back(unit(static_cast<char>(u), static_cast<char>(r), s, t));
	}
	in.close();
	return true;
}


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
		//out << unitRef.getUnitID() << unitRef.getRoomID() << unitRef.getStatus() << unitRef.getTime() << endl;
		out.close();
		return true;
	}
	else
	{
		cout << "Unit ID already exists" << endl;
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
