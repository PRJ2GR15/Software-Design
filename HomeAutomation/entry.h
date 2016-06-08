//========================================================================
// FILENAME : <Entry.h>
// CREATED : <18/05-2016>
// AUTHOR : <Anders Brondbjerg Knudsen>
// DESCR. : <Header for Entry>
//
//------------------------------------------------------------------------
//
// REV. DATE/AUTHOR CHANGE DESCRIPTION
// 1.0 <18/05-2016/Anders Brondbjerg Knudsen> <Oprettelse af Entry>
// 1.1 <19/05-2016/Anders Brondbjerg Knudsen> <DayOfWeek attibut fjernes. Bliver i stedet en vector som indeholder dag og entry objekter i Unit. 
// 1.2 <19/05-2016/Anders Brondbjerg Knudsen> <Ændret så implementering ikke er inline>
// 1.3 <24/05-2016/Anders Brondbjerg Knudsen> <Tilføjelse af EntryID>
//========================================================================
#ifndef ENTRY_H
#define ENTRY_H

#include <iostream>

using namespace std;


//=====================================
// CLASS : Entry 
// DESCR.: Indeholder data om hvornår enheden skal aktiveres og slukke
//=====================================

class Entry
{
public: 
	Entry();
    Entry(unsigned char entryID,unsigned char hour, unsigned char min, bool action);
    bool setHour(unsigned char hour);
	unsigned char getHour()const;
    bool setMin(unsigned char min);
	unsigned char getMin()const;
    bool setAction(bool action);
	bool getAction()const;
	friend istream& operator>>(istream& is, Entry& obj);
    unsigned char EntryID()const { return +entryID_;}
	
private:
    unsigned char entryID_;
	unsigned char hour_;
	unsigned char min_;
	bool action_;
};



#endif
