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
    setEntries();
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

//=============================================================
// METHOD : Return status for enhed
// DESCR. : 
//=============================================================

bool Unit::getStatus() const
{
	return status_;
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
bool Unit::storeEntry(int day, Entry& obj)
{
    if (entryRegister_[day].size() <=maxEntries)
	{
		entryRegister_[day].push_back(obj);
        EntriesID.erase(remove(EntriesID.begin(), EntriesID.end(), obj.EntryID()), EntriesID.end());
		return true;
	}
	else
		return false;
}

//=============================================================
// METHOD : Compare Entry. 
// DESCR. : Benyttes for at tjekke om en entry allerede findes i registret for den dag.
//=============================================================
bool Unit::compareEntry(Entry& obj,int d)
{
	
	int max = entryRegister_[d].size();
	
		
	for (int i = 0; i < max;i++)
	{
        if ( (entryRegister_[d][i].getHour() == obj.getHour() && (entryRegister_[d][i].getMin() == obj.getMin()) && (entryRegister_[d][i].getAction() == obj.getAction())))
            return true;
			
	}
	return false; //Samme tidsplan findes ikke
}

//=============================================================
// METHOD : Delete Entry. 
// DESCR. : Benyttes for at slette en Entry fra Vectoren
//=============================================================
bool Unit::deleteEntry(unsigned char entryID)
{
    
    for(int i = 0; i < days; i++)
    {
        for(int j = entryRegister_[i].size()-1; j >= 0; j--)
        {
            if(entryID == entryRegister_[i][j].EntryID())
            {
                entryRegister_[i].erase(entryRegister_[i].begin() + j);
            }
        }
    }
    addDeletedEntry(entryID);

    return false;
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
// METHOD : getSize. 
// DESCR. : Return størrelse på entryRegister for alle dage
//=============================================================

unsigned char Unit::getSize()const
{
	
	unsigned char size=0;
	
	for(int i= 0; i<7;i++)
	{
		size += entryRegister_[i].size();
	}
	return size;
}


//=============================================================
// METHOD : setEntries. 
// DESCR. : Sætter Entries id, så der kan hentes et ID til alle tries.
//          Da de oprettes i par med en tænd og sluk, så er der 70 Entries ID er benytte
//=============================================================

void Unit::setEntries()
{
    unsigned char MaxEntries=70; //Da der maks kan være 10 par entries per dag.

    for(unsigned char i = 1; i <= MaxEntries ; i++ )
    {
        EntriesID.push_back(i);
    }
}


//=============================================================
// METHOD : getIDEntry. 
// DESCR. : Benyttes for at return et ID til en entry. 
//=============================================================


unsigned char Unit::getIDEntry()
{
    if(!EntriesID.empty())
    {
        unsigned char ID = EntriesID.back();
        EntriesID.pop_back();
        return ID;
    }
}

//=============================================================
// METHOD : addDeleteEntry. 
// DESCR. : Benyttes for tilføje et ID, hvis en tidsplan er slettet.  
//=============================================================


void Unit::addDeletedEntry(unsigned char ID)
{
  if(find(EntriesID.begin(), EntriesID.end(), ID) != EntriesID.end())
  {

  }
  else
      EntriesID.push_back(ID);
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

