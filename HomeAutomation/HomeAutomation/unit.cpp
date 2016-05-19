//========================================================================
// FILENAME : <unit.cpp>
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


#include "unit.h"
#include <fstream>


//=============================================================
// METHOD : Explicit Constructor
// DESCR. : 
//=============================================================

unit::unit(unsigned char unitID, char roomID, unsigned char houseCode, bool status)
{
	setUnitID(unitID);
	roomID_ = roomID;
	setHouseCode(houseCode);
	status_ = status;
}

//=============================================================
// METHOD : Sætter UnitID
// DESCR. : Tilladte værdier fra 1 til 255 
//=============================================================

void unit::setUnitID(char unitID)
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

char unit::getUnitID() const
{
	return unitID_;
}

//=============================================================
// METHOD : Sætter RoomID
// DESCR. : Ingen validering
//=============================================================

void unit::setRoomID(char roomID)
{
	roomID_ = roomID;
}


//=============================================================
// METHOD : Returner RoomID
// DESCR. : 
//=============================================================

char unit::getRoomID() const
{
	return roomID_;
}

//=============================================================
// METHOD : Sætter HouseCode
// DESCR. : Tilladte værdier fra 1 til 15
//=============================================================

void unit::setHouseCode(char houseCode)
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

unsigned char unit::getHouseCode() const
{
	return houseCode_;
}

//=============================================================
// METHOD : Sæt status for en enhed 
// DESCR. : 1 = tændt. 0 = slukket
//=============================================================

void unit::setStatus(bool status)
{
	status_ = status;
}

bool unit::getStatus() const
{
	return status_;
}

//=============================================================
// METHOD : Print
// DESCR. : Printer information om Unit
//=============================================================

void unit::print() const
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


ostream &operator<<(ostream& os, const unit& obj)
{
	obj.print();

	return os;
}

//=============================================================
// METHOD : Input operator
// DESCR. : Giver mulighed for at indlæse data til objekt. 
//=============================================================


istream& operator>>(istream& is, unit& obj)
{
	is >> obj.unitID_;
	is >> obj.roomID_;
	is >> obj.houseCode_;
	is >> obj.status_;
	
	return is;
}
