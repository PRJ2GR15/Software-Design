#pragma once
#include <ostream>
#include <iostream>
#include <QtCore>

using namespace std;

//Unit header. 

class unit
{
public: //Constructor
	unit(unsigned char unitID, char roomID, unsigned char houseCode, bool status)
	{
		setUnitID(unitID);
        roomID_ = roomID;
		setHouseCode(houseCode);
		status_ = status;
		
	}

//Metode for at sætte UnitID -- Tilladte værdier fra 1 til 255
    void setUnitID(uchar unitID)
	{
		if (unitID >= 1 && unitID <= 255)
			unitID_ = unitID;
		else
			return;
	}

//Metode for at returner UnitID 
    uchar getUnitID() const
	{
		return unitID_;
	}
//Metode for at sætte roomID. Ingen validering
    void setRoomID(uchar roomID)
	{
		roomID_ = roomID;
	}

//Metode for at returner RoomID
    uchar getRoomID() const
	{
		return roomID_;
	}
//Metode for at sætte HouseCode -- Tilladte værdier fra 1 til 15
    void setHouseCode(uchar houseCode)
	{
		if (houseCode >= 1 && houseCode <= 15)
			houseCode_ = houseCode;
		else
			return;
	}
//Metode for at returner houseCode
	unsigned char getHouseCode()const
	{
		return houseCode_;
	}

//Metode for at sætte status
	void setStatus(bool status)
	{
		status_ = status;
	}

//Metode for at returner status på enheden
	bool getStatus() const
	{
		return status_;
	}
//Metode for at printe oplysninger fra objektet
	void print()const;

//Operator>> for at indlæse data til objekt
	friend istream& operator>>(istream& is, unit& obj);


private:
	unsigned char unitID_; 
	char roomID_;
	unsigned char houseCode_;
	bool status_;
	
};
//Operator << for at printe objektets oplysninger
	ostream& operator<<(ostream& os, const unit& obj);
