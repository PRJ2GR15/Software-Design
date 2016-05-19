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
//========================================================================
#include "entry.h"

#pragma once
#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

//=====================================
// CLASS : Unit
// DESCR. : Indeholder data om Units. 
// Dets UnitID, RoomID, Housecode og dets status.
//=====================================


class unit
{
public: 
	unit(unsigned char unitID, char roomID, unsigned char houseCode, bool status);
	void setUnitID(char unitID);
	char getUnitID() const;
	void setRoomID(char roomID);
	char getRoomID() const;
	void setHouseCode(char houseCode);
	unsigned char getHouseCode()const;
	void setStatus(bool status);
	bool getStatus() const;
	void print()const;
	friend istream& operator>>(istream& is, unit& obj);
	bool loadEntryData();

private:
	unsigned char unitID_; 
	char roomID_;
	unsigned char houseCode_;
	bool status_;
	vector <vector<entry> > entryRegister_[6]; // Oprettelse et two 
 
};

	ostream& operator<<(ostream& os, const unit& obj);
