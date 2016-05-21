﻿//========================================================================
// FILENAME : <Entry.cpp>
// CREATED : <18/05-2016>
// AUTHOR : <Anders Brondbjerg Knudsen>
// DESCR. : <Implementering af Entry>
//
//------------------------------------------------------------------------
//
// REV. DATE/AUTHOR CHANGE DESCRIPTION
// 1.0 <18/05-2016/Anders Brondbjerg Knudsen> <Implementering af entry. Print, operator>> og operator<< >
// 1.1 <19/05-2016/Anders Brondbjerg Knudsen> <Opdatering af metoder efter attribut dayOfWeek fjernet.> 
// 1.2 <19/05-2016/Anders Brondbjerg Knudsen> <Ændret så implementering ikke er inline>
//========================================================================


#include "Entry.h"

//=============================================================
// METHOD : Explicit Constructor
// DESCR. : 
//=============================================================

Entry::Entry()
{
}

Entry::Entry(unsigned char hour, unsigned char min, bool action)
{
	setHour(hour);
	setMin(min);
    setAction(action);
}

//=============================================================
// METHOD : Sætter hour
// DESCR. : Tilladte værdier fra 0 til 23 
//=============================================================


void Entry::setHour(unsigned char hour)
{
	if (hour >= 0 && hour <= 23)
		hour_ = hour;
	else
		return;
}

//=============================================================
// METHOD : Returner Hour
// DESCR. : 
//=============================================================

unsigned char Entry::getHour() const
{
	return hour_;
}

//=============================================================
// METHOD : Sætter min
// DESCR. : Tilladte værdier fra 0 til 59
//=============================================================

void Entry::setMin(unsigned char min)
{
	if (min >= 0 && min <= 59)
		min_ = min;
	else
		return;
}

//=============================================================
// METHOD : Returner min
// DESCR. : 
//=============================================================

unsigned char Entry::getMin() const
{
	return min_;
}

//=============================================================
// METHOD : Sætter action. 
// DESCR. : 1 = Planlægges at skulle tændes. 
//          0 = Planlægges at skulle slukkes.
//=============================================================

void Entry::setAction(bool action)
{
	action_ = action;

}

//=============================================================
// METHOD : Returner action
// DESCR. : 
//=============================================================

bool Entry::getAction() const
{
	return action_;
}


//=============================================================
// METHOD : Print
// DESCR. : Printer information om Entry
//=============================================================


void Entry::print()const
{
	cout << +hour_ << " " << +min_ <<  " " << action_ << endl;
}

//=============================================================
// METHOD : Print Operator 
// DESCR. : Giver mulighed for at printe med objekt navn
//=============================================================


ostream &operator<<(ostream& os, const Entry& obj)
{
	os << +obj.getHour()<< " ";
	os << +obj.getMin() << " ";
	os << +obj.getAction() << endl;

	return os;
	
}

//=============================================================
// METHOD : Input operator
// DESCR. : Giver mulighed for at indlæse data til objekt. 
//=============================================================


istream& operator>>(istream& is, Entry& obj)
{
	is >> obj.hour_;
	is >> obj.min_;
	is >> obj.action_;

	return is;
}