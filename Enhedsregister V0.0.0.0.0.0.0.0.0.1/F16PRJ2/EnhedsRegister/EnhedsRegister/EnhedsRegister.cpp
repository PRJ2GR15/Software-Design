#include "EnhedsRegister.h"

EnhedsRegister::EnhedsRegister()
{
	outputFile = "./register.txt";
	loadData();
}

bool EnhedsRegister::loadData()
{
	unit tmpUnit(0x00, 0x00, false, 0);
	string line;
	char u = 0x00; char r = 0x00; bool s = false; int t = 0;
	in.open(outputFile);
	if(in.is_open())
	{
		while (getline(in, line))
		{
			istringstream is(line);
			is >> tmpUnit;
			unitRegister_.push_back(tmpUnit);
			/*is >> u >> r >> s >> t;*/
/*			if (storeUnit(unit(u, r, s, t)))
				cout << "Unit Stored" << endl;
			else
				cout << "FAILED" << endl;*/
		}
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
