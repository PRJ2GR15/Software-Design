#include "EnhedsRegister.h"

EnhedsRegister::EnhedsRegister()
{
    //outputFile = "register.txt";
	loadData();
}

bool EnhedsRegister::loadData()
{
	//unit tmpUnit(0x00, 0x00, false, 0);
	int u = 0x00; int r = 0x00; bool s = false; int t = 0;
    string path1 = "register.txt";
    QString path = QDir::currentPath();
    path.append("/registry.txt");
    //QFile file(path); !file.open(QIODevice::ReadOnly)
    in.open(path1,ios::in);
    if (!in)
	{
		cerr << "Filen findes ikke" << endl;
		return false;
	}
		
    while (!in.eof())
	{
		in >> u >> r >> s >> t;
		if (!compareID(u))
            unitRegister_.push_back(unit(static_cast<uchar>(u), static_cast<uchar>(r), s, t));
		else
			cout << "Unit already exists" << endl;
	}
	in.close();
	return true;
}

bool EnhedsRegister::storeUnit(unit& unitRef)
{
	if (!compareID(unitRef.getUnitID()))
	{
		unitRegister_.push_back(unitRef);
        return true;
	}
    else
    {
        vector<unit>::iterator iter;
        for(iter = unitRegister_.begin(); iter != unitRegister_.end(); ++iter) {
            if(iter->getUnitID() == unitRef.getUnitID())
                *iter = unitRef;
        }
    }
}

bool EnhedsRegister::compareID(uchar unitID) const
{
	vector<unit>::const_iterator iter;
	for (iter = unitRegister_.begin(); iter != unitRegister_.end(); ++iter)
	{
		if (unitID == (*iter).getUnitID())
			return true; //ID Findes allerede
	}
	return false; //ID Findes ikke

}

bool EnhedsRegister::updateStatus(uchar unitID, bool status)
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

bool EnhedsRegister::deleteUnit(uchar unitID)
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

bool EnhedsRegister::modifyUnit(uchar unitID, uchar roomID)
{
	return true;
}

/*bool EnhedsRegister::updateTime(char roomID, int placeholder)
{
}*/

bool EnhedsRegister::updateTime(uchar roomID, int placeholder)
{
	return true;
}

EnhedsRegister::~EnhedsRegister()
{
}
