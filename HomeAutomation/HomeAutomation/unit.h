//========================================================================
// FILENAME : <Unit.h>
// CREATED : <17/05-2016>
// AUTHOR : <Anders Brondbjerg Knudsen>
// DESCR. : <Headerfilen for Unit>
//
//------------------------------------------------------------------------
//
// REV. DATE/AUTHOR CHANGE DESCRIPTION
// 1.0 <rev. date/author> <Change description>
//========================================================================


#pragma once
#include <iostream>

using namespace std;

//=====================================
// CLASS : Unit
// DESCR. : Indeholder data om Units. 
// Dets UnitID, RoomID, Housecode og dets status.
//=====================================


class unit
{
public: 
	
	//=============================================================
	// METHOD : Explicit Constructor
	// DESCR. : 
	//=============================================================

	unit(unsigned char unitID, char roomID, unsigned char houseCode, bool status)
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
	void setUnitID(char unitID)
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

	char getUnitID() const
	{
		return unitID_;
	}

	//=============================================================
	// METHOD : Sætter RoomID
	// DESCR. : Ingen validering
	//=============================================================

	void setRoomID(char roomID)
	{
		roomID_ = roomID;
	}

	//=============================================================
	// METHOD : Returner RoomID
	// DESCR. : 
	//=============================================================

	char getRoomID() const
	{
		return roomID_;
	}

	//=============================================================
	// METHOD : Sætter HouseCode
	// DESCR. : Tilladte værdier fra 1 til 15
	//=============================================================

	void setHouseCode(char houseCode)
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

	unsigned char getHouseCode()const
	{
		return houseCode_;
	}

	//=============================================================
	// METHOD : Sæt status for en enhed 
	// DESCR. : 1 = tændt. 0 = slukket
	//=============================================================

	void setStatus(bool status)
	{
		status_ = status;
	}

	//=============================================================
	// METHOD : Returner status for enheden
	// DESCR. : 
	//=============================================================

	bool getStatus() const
	{
		return status_;
	}

	void print()const;


	friend istream& operator>>(istream& is, unit& obj);


private:
	unsigned char unitID_; 
	char roomID_;
	unsigned char houseCode_;
	bool status_;
	
};

	ostream& operator<<(ostream& os, const unit& obj);
