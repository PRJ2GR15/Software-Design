//========================================================================
// FILENAME : <Unit.h>
// CREATED : <17/05-2016>
// AUTHOR : <Anders Brondbjerg Knudsen>
// DESCR. : <Headerfilen for Unit>
//
//------------------------------------------------------------------------
//
// REV. DATE/AUTHOR CHANGE DESCRIPTION
// 1.0 <17/05-2016/Anders Brondbjerg Knudsen> <Oprettelse af Unit>
// 1.1 <19/05-2016/Anders Brondbjerg Knudsen> <Tilføjelse af Entry>
// 1.2 <19/05-2016/Anders Brondbjerg Knudsen> <Ændret så implementering ikke er inline> 
// 1.3 <19/05-2016/Anders Brondbjerg Knudsen> <Ændret så implementering ikke er inline> 
// 1.3 <20/05-2016/Anders Brondbjerg Knudsen> <Tilføjelse af metoder til Entry> 
//========================================================================
#ifndef UNIT_H
#define UNIT_H

#include "Entry.h"
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

//=====================================
// CLASS : Unit
// DESCR. : Indeholder data om Units. 
// Dets UnitID, RoomID, Housecode og dets status.
//=====================================

const int days= 7; //Bruger i Vector- Antal dage- 0=mandag, 1 = tirsdag, 2 = onsdag, 3 = torsdag, 4 = fredag, 5= lørdag, 6= søndag.
const int maxEntries = 20; //Maks antal entries som kan tilføjes. Per dag.

class Unit
{
public: 
	Unit(unsigned char unitID, unsigned char roomID, unsigned char houseCode, bool status);
    //UNIT/ROOM ID MANIPULATORS
	void setUnitID(unsigned char unitID);
	unsigned char getUnitID() const;
	void setRoomID(unsigned char roomID);
	unsigned char getRoomID() const;
	void setHouseCode(unsigned char houseCode);
	unsigned char getHouseCode()const;
    //UNIT/ROOM ID MANIPULATORS END

    //STATUS + PRINT FUNKTIONER
	void setStatus(bool status);
	bool getStatus() const;
	
	friend istream& operator>>(istream& is, Unit& obj);
    //STATUS + PRINT FUNKTIONER END

    void initialEntry();
    //HENT OG STORE ENTRY FUNKTIONER
	bool storeEntry(int day,Entry&obj);
    //HENT OG STORE ENTRY FUNKTIONER END

    bool compareEntry(Entry&,int);
    //DELETE OG UPDATE ENTRY FUNKTIONER
    bool deleteEntry(unsigned char entryID);
	bool deleteDayEntry(int day);
	
    //DELETE OG UPDATE ENTRY FUNKTIONER END

	
	unsigned char getSize()const;

    void setEntries();
    unsigned char getIDEntry();
    void addDeletedEntry(unsigned char ID);

    const vector<vector<Entry> >& getEntryRegisterRef() { return entryRegister_; }
private:
	unsigned char unitID_; 
	unsigned char roomID_;
	unsigned char houseCode_;
	bool status_;
    vector<vector<Entry> > entryRegister_; // Oprettelse et to dimensionel. Indeholder 7 dage med entry objekter.
    vector<unsigned char> EntriesID;
	
};

	
#endif
