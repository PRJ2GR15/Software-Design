//========================================================================
// FILENAME : <unit.cpp>
// CREATED : <17/05-2016>
// AUTHOR : <Anders Brondbjerg Knudsen>
// DESCR. : <Implementering af Unit>
//
//------------------------------------------------------------------------
//
// REV. DATE/AUTHOR CHANGE DESCRIPTION
// 1.0 <rev. date/author> <Change description>
//========================================================================


#include "unit.h"


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
