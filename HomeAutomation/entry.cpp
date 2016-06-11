//========================================================================
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
// 1.3 <24/05-2016/Anders Brondbjerg Knudsen> <Tilføjelse af EntryID>
//========================================================================


#include "Entry.h"

//=============================================================
// METHOD : Explicit Constructor
// DESCR. : 
//=============================================================

Entry::Entry()
{
}

Entry::Entry(unsigned char entryID, unsigned char hour, unsigned char min, bool action)
{
    entryID_= entryID;
    setHour(hour);
    setMin(min);
    setAction(action);
}

//=============================================================
// METHOD : Sætter hour
// DESCR. : Tilladte værdier fra 0 til 23 
//=============================================================


bool Entry::setHour(unsigned char hour)
{
	if (hour >= 0 && hour <= 23)
        {
		hour_ = hour;
                return true;
        }
	else
                return false;
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

bool Entry::setMin(unsigned char min)
{
	if (min >= 0 && min <= 59)
        {
		min_ = min;
                return true;
        }
	else
                return false;
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

bool Entry::setAction(bool action)
{
	action_ = action;
        return true;

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
// METHOD : Input operator
// DESCR. : Giver mulighed for at indlæse data til objekt. 
//=============================================================


istream& operator>>(istream& is, Entry& obj)
{   is >> obj.entryID_;
	is >> obj.hour_;
	is >> obj.min_;
	is >> obj.action_;

	return is;
}
