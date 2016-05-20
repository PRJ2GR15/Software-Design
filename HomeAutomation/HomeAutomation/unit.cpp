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
// 1.3 <20/05-2016/Anders Brondbjerg Knudsen> <Tilføjelse af metoder til Entry> 
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
	loadEntryData();
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
// METHOD : Initialiserer Entry. 
// DESCR. : Initialiserer størrelse på Entry. 7*20. Da vi har 7 dage, med maks 20 entries. 
//=============================================================

void Unit::initialEntry()
{
	vector<Entry>temp(0);
	vector<vector<Entry> > temp2(days, temp);
	entryRegister_ = temp2;
}

//=============================================================
// METHOD : Store Entry. 
// DESCR. : Benyttes for at ligge en tidsplan ind i Unit. 
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

//=============================================================
// METHOD : Compare Entry. 
// DESCR. : Benyttes for at tjekke om to objekter er ens.
//=============================================================

bool Unit::compareEntry(Entry& obj,int d) const
{
	
	int max = entryRegister_[d].size();
	
		
	for (int i = 0; i < max;i++)
	{
            if ((entryRegister_[d][i].getHour() == obj.getHour() && (entryRegister_[d][i].getMin() == obj.getMin()) && (entryRegister_[d][i].getAction() == obj.getAction())))
				return true;
			
	}
	return false; //Samme tidsplan findes ikke
}

//=============================================================
// METHOD : Delete Entry. 
// DESCR. : Benyttes for at slette en Entry fra Vectoren
//=============================================================

bool Unit::deleteEntry(int day,int place)
{
	entryRegister_[day].erase(entryRegister_[day].begin() + place);
	return true;
}

//=============================================================
// METHOD : DeleteDayEntry. 
// DESCR. : Benyttes for at slette en dags tidsplan
//=============================================================

bool Unit::deleteDayEntry(int day)
{
	entryRegister_[day].clear();
	return true;
}

//=============================================================
// METHOD : deleteEntry. 
// DESCR. : Benyttes for slette tidsplan
//=============================================================

bool Unit::deleteEntry()
{
	entryRegister_.clear();
	return true;
}

//=============================================================
// METHOD : UpdateEntry. 
// DESCR. : Benyttes for at opdater allerede eksisterende tidsplan
//=============================================================

bool Unit::updateEntry(int day, int place, unsigned char hour, unsigned char min, bool action)
{
	entryRegister_[day][place].setHour(hour);
	entryRegister_[day][place].setMin(min);
	entryRegister_[day][place].setAction(action);
	return true;
}

//=============================================================
// METHOD : Print metode. 
// DESCR. : Print alle Entries som er tilføjet i pågældende Unit
//=============================================================

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

bool Unit::loadEntryData()
{
	int d = 0x00, h = 0x00, m = 0x00; bool a = false;

	ifstream entryFile;

		entryFile.open("entry.txt", ios::in);
	
		if (!entryFile)
		{
			cerr << "Filen findes ikke" << endl;
			return false;
		}
	
		while (!entryFile.eof())
		{
			
			entryFile >>d >> h >> m >> a;
			Entry tempObj(h, m, a);
			storeEntry(d, tempObj);
			
		}
		entryFile.close();
		return true;


}

//=============================================================
// METHOD : StoreEntrydata 
// DESCR. : Benyttes for at gemme oprettede entries til et txt.file 
//=============================================================



bool Unit::storeEntryData()
{
	ofstream saveData;

	saveData.open("entry.txt");

	if(!saveData)
	{
		cerr << "Filen findes ikke" << endl;
		return false;
	}

	for (int i = 0; i < 7; i++) 
	{
		for (int j = 0; j < entryRegister_[i].size(); j++)
		{
			saveData << i << " ";
			saveData << entryRegister_[i][j];
		}
	}

	saveData.close();
	return true;
}


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

