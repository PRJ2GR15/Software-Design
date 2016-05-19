//========================================================================
// FILENAME : <Unit.cpp>
// CREATED : <17/05-2016>
// AUTHOR : <Anders Brondbjerg Knudsen>
// DESCR. : <Implementering af Unit>
//
//------------------------------------------------------------------------
//
// REV. DATE/AUTHOR CHANGE DESCRIPTION
// 1.0 <17/05-2016/Anders Brondbjerg Knudsen> <Oprettelse af Unit>
// 1.1 <19/05-2016/Anders Brondbjerg Knudsen> <Tilføjelse af Entry>
// 1.2 <19/05-2016/Anders Brondbjerg Knudsen> <Ændret så implementering ikke er inline> 
//========================================================================


#include "Unit.h"
#include <fstream>


//=============================================================
// METHOD : Explicit Constructor
// DESCR. : 
//=============================================================

Unit::Unit(unsigned char unitID, unsigned char roomID, unsigned char houseCode, bool status)
{
	setUnitID(unitID);
	roomID_ = roomID;
	setHouseCode(houseCode);
	status_ = status;

	initialEntry();
	
}

//=============================================================
// METHOD : Sætter UnitID
// DESCR. : Tilladte værdier fra 1 til 255 
//=============================================================

void Unit::setUnitID(unsigned char unitID)
{
	if (unitID >= 1 && unitID <= 255)
		unitID_ = unitID;
	else
		return;
}

//=============================================================
// METHOD : Returner UnitID
// DESCR. : 
//=============================================================

unsigned char Unit::getUnitID() const
{
	return unitID_;
}

//=============================================================
// METHOD : Sætter RoomID
// DESCR. : Ingen validering
//=============================================================

void Unit::setRoomID(unsigned char roomID)
{
	roomID_ = roomID;
}


//=============================================================
// METHOD : Returner RoomID
// DESCR. : 
//=============================================================

unsigned char Unit::getRoomID() const
{
	return roomID_;
}

//=============================================================
// METHOD : Sætter HouseCode
// DESCR. : Tilladte værdier fra 1 til 15
//=============================================================

void Unit::setHouseCode(unsigned char houseCode)
{
	if (houseCode >= 1 && houseCode <= 15)
		houseCode_ = houseCode;
	else
		return;

}

//=============================================================
// METHOD : Returner HouseCode
// DESCR. : 
//=============================================================

unsigned char Unit::getHouseCode() const
{
	return houseCode_;
}

//=============================================================
// METHOD : Sæt status for en enhed 
// DESCR. : 1 = tændt. 0 = slukket
//=============================================================

void Unit::setStatus(bool status)
{
	status_ = status;
}

bool Unit::getStatus() const
{
	return status_;
}

//=============================================================
// METHOD : Print
// DESCR. : Printer information om Unit
//=============================================================

void Unit::print() const
{
	cout << "\nUnitID: " << static_cast<int>(getUnitID()) 
		 << "\nRoomID: " << static_cast<int>(getRoomID()) 
		 << "\nHouseCodeNr: "<< static_cast<int>(getHouseCode()) << endl;

	if (getStatus() == true)
		cout << "Enheden er aktiv" << endl;
	else
		cout << "Enheden er deactiveret" << endl;

}

//=============================================================
// METHOD : Compare Entry. 
// DESCR. : Benyttes for at tjekke om to objekter er ens.
//=============================================================

bool Unit::storeEntry(int day,Entry& obj)
{
	if ((entryRegister_[day].size() <=maxEntries) & (!compareEntry(obj,day)))
	{
		entryRegister_[day].push_back(obj);
		return true;
	}
	else
		return false;
}

bool Unit::compareEntry(Entry& obj,int d) const
{
	
	int max = entryRegister_[d].size();
	
		
	for (int i = 0; i < max;i++)
	{
			if ((entryRegister_[d][i].getHour() == obj.getHour() & (entryRegister_[d][i].getMin() == obj.getMin()) && (entryRegister_[d][i].getAction() == obj.getAction())))
				return true;
			
	}
	return false; //Samme tidsplan findes ikke
}


//=============================================================
// METHOD : Initialiserer Entry. 
// DESCR. : Initialiserer størrelse på Entry. 7*20. Da vi har 7 dage, med maks 20 entries. 
//=============================================================

void Unit::initialEntry()
{
	vector<Entry>temp(0);
	vector<vector<Entry> > temp2(days, temp);
	entryRegister_ = temp2;
}

void Unit::printEntry() const
{
	
	for (auto row : entryRegister_)
	{
		for (auto col : row)
			cout << col << endl;
	}
}

//=============================================================
// METHOD : Load data for Entry. 
// DESCR. : Indlæser gemt data fra txt.fil ved allerede oprettede tidsplaner
//=============================================================

//bool unit::loadEntryData()
//{
//	int h = 0x00, m = 0x00; bool a = false;
//
//	ifstream entryFile;
//
//		entryFile.open("entry.txt", ios::in);
//	
//		if (!entryFile)
//		{
//			cerr << "Filen findes ikke" << endl;
//			return false;
//		}
//	
//		while (!entryFile.eof())
//		{
//			entryFile >> h >> m >> a;
//
//			entryRegister_.push_back(entry(static_cast<unsigned char>(h), static_cast<unsigned char> (m), static_cast<unsigned char> (d), a));
//		}
//		entryFile.close();
//		return true;
//
//
//}

//=============================================================
// METHOD : Print Operator 
// DESCR. : Giver mulighed for at printe med objekt navn
//=============================================================


ostream &operator<<(ostream& os, const Unit& obj)
{
	obj.print();
	obj.printEntry();
	return os;
}

//=============================================================
// METHOD : Input operator
// DESCR. : Giver mulighed for at indlæse data til objekt. 
//=============================================================


istream& operator>>(istream& is, Unit& obj)
{
	is >> obj.unitID_;
	is >> obj.roomID_;
	is >> obj.houseCode_;
	is >> obj.status_;
	
	return is;
}

