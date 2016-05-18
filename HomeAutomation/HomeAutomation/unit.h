//========================================================================
// FILENAME : <filename>
// CREATED : <Creation date>
// AUTHOR : <Author>
// DESCR. : <Description of file contents>
//
//------------------------------------------------------------------------
//
// REV. DATE/AUTHOR CHANGE DESCRIPTION
// 1.0 <rev. date/author> <Change description>
//========================================================================


#pragma once
#include <iostream>

using namespace std;


class unit
{
public: 
	
	//=============================================================
	// METHOD : 
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
	// METHOD : 
	// DESCR. : 
	//=============================================================
	void setUnitID(char unitID)
	{
		if (unitID >= 1 && unitID <= 255)
			unitID_ = unitID;
		else
			return;
	}

	//=============================================================
	// METHOD : 
	// DESCR. : 
	//=============================================================

	char getUnitID() const
	{
		return unitID_;
	}

	//=============================================================
	// METHOD : 
	// DESCR. : 
	//=============================================================

	void setRoomID(char roomID)
	{
		roomID_ = roomID;
	}

	//=============================================================
	// METHOD : 
	// DESCR. : 
	//=============================================================

	char getRoomID() const
	{
		return roomID_;
	}

	//=============================================================
	// METHOD : 
	// DESCR. : 
	//=============================================================

	void setHouseCode(char houseCode)
	{
		if (houseCode >= 1 && houseCode <= 15)
			houseCode_ = houseCode;
		else
			return;
	}

	//=============================================================
	// METHOD : 
	// DESCR. : 
	//=============================================================

	unsigned char getHouseCode()const
	{
		return houseCode_;
	}

	//=============================================================
	// METHOD : 
	// DESCR. : 
	//=============================================================

	void setStatus(bool status)
	{
		status_ = status;
	}

	//=============================================================
	// METHOD : 
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
