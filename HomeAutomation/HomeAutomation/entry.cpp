//========================================================================
// FILENAME : <entry.cpp>
// CREATED : <18/05-2016>
// AUTHOR : <Anders Brondbjerg Knudsen>
// DESCR. : <Implementering af entry>
//
//------------------------------------------------------------------------
//
// REV. DATE/AUTHOR CHANGE DESCRIPTION
// 1.0 <rev. date/author> <Change description>
//========================================================================


#include "entry.h"

//=============================================================
// METHOD : Print
// DESCR. : Printer information om entry
//=============================================================

void entry::print()const
{
	cout << +hour_ << " " << +min_ << " " << +dayOfWeek_ << " " << action_ << endl;
}

//=============================================================
// METHOD : Print Operator 
// DESCR. : Giver mulighed for at printe med objekt navn
//=============================================================


ostream &operator<<(ostream& os, const entry& obj)
{
	obj.print();

	return os;
}

//=============================================================
// METHOD : Input operator
// DESCR. : Giver mulighed for at indlæse data til objekt. 
//=============================================================


istream& operator>>(istream& is, entry& obj)
{
	is >> obj.hour_;
	is >> obj.min_;
	is >> obj.dayOfWeek_;
	is >> obj.action_;

	return is;
}
