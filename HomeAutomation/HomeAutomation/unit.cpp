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


#include "unit.h"


//=============================================================
// METHOD : 
// DESCR. : 
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
// METHOD : 
// DESCR. : 
//=============================================================


ostream &operator<<(ostream& os, const unit& obj)
{
	obj.print();

	return os;
}

//=============================================================
// METHOD : 
// DESCR. : 
//=============================================================


istream& operator>>(istream& is, unit& obj)
{
	is >> obj.unitID_;
	is >> obj.roomID_;
	is >> obj.houseCode_;
	is >> obj.status_;
	
	return is;
}
