﻿//========================================================================
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
//========================================================================
#include "Entry.h"

#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>

using namespace std;

//=====================================
// CLASS : Unit
// DESCR. : Indeholder data om Units. 
// Dets UnitID, RoomID, Housecode og dets status.
//=====================================

const int days= 7; //Bruger i Vector- Antal dage- 0=mandag, 1 = tirsdag, 2 = onsdag, 3 = torsdag, 4 = fredag, 5= lørdag, 6= søndag.
const int maxEntries = 20; //Maks antal entries som kan tilføjes. 

class Unit
{
public: 
	Unit(unsigned char unitID, unsigned char roomID, unsigned char houseCode, bool status);
	void setUnitID(unsigned char unitID);
	unsigned char getUnitID() const;
	void setRoomID(unsigned char roomID);
	unsigned char getRoomID() const;
	void setHouseCode(unsigned char houseCode);
	unsigned char getHouseCode()const;
	void setStatus(bool status);
	bool getStatus() const;
	void print()const;
	friend istream& operator>>(istream& is, Unit& obj);
	bool loadEntryData();
	bool storeEntry(int day,Entry&obj);
	bool compareEntry(Entry&,int)const;
	void initialEntry();
	void printEntry()const;
private:
	unsigned char unitID_; 
	unsigned char roomID_;
	unsigned char houseCode_;
	bool status_;
	vector <vector<Entry> > entryRegister_; // Oprettelse et to dimensionel. Indeholder 7 dage med entry objekter. 
	
};

	ostream& operator<<(ostream& os, const Unit& obj);
