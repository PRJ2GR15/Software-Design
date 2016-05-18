#include "unit.h"

//NOTE: Når GUI så overflødig.... 
//Print funktion for at printe oplysninger fra Unit
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

//Operator<< mulighed for at printe hele objekter ved navn
ostream& operator<<(ostream& os, const unit& obj)
{
	obj.print();

	return os;
}

//Operator >> for at kunne indlæse data til objekt
istream& operator>>(istream& is, unit& obj)
{
	is >> obj.unitID_;
	is >> obj.roomID_;
	is >> obj.houseCode_;
	is >> obj.status_;
	
	return is;
}
