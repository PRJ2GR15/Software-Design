//========================================================================
// FILENAME : <entry.h>
// CREATED : <18/05-2016>
// AUTHOR : <Anders Brondbjerg Knudsen>
// DESCR. : <Header for entry>
//
//------------------------------------------------------------------------
//
// REV. DATE/AUTHOR CHANGE DESCRIPTION
// 1.0 <rev. date/author> <Oprettelse af entry>
//========================================================================

#pragma once
#include <iostream>

using namespace std;


//=====================================
// CLASS : Entry
// DESCR. : Indeholder data om hvornår enheden skal aktiveres og slukke
//=====================================

class entry
{
public: 

	//=============================================================
	// METHOD : Explicit Constructor
	// DESCR. : 
	//=============================================================

	entry(unsigned char hour, unsigned char min, unsigned char dayOfWeek, bool action)
	{
		setHour(hour);
		setMin(min);
		setDayOfWeek(dayOfWeek);
		setAction(action);
	}
	
	//=============================================================
	// METHOD : Sætter hour
	// DESCR. : Tilladte værdier fra 0 til 23 
	//=============================================================

	void setHour(unsigned char hour)
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

	unsigned char getHour()const
	{
		return hour_;
	}

	//=============================================================
	// METHOD : Sætter min
	// DESCR. : Tilladte værdier fra 0 til 59
	//=============================================================

	void setMin(unsigned char min)
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

	unsigned char getMin()const
	{
		return min_;
	}
	
	//=============================================================
	// METHOD : Sætter dayOfWeek
	// DESCR. : Tilladte værdier fra 1 til 7. Står for ugedagene. 1 = mandag... 7 = søndag. 
	//=============================================================

	void setDayOfWeek(unsigned char dayOfWeek)
	{
		if (dayOfWeek >= 1 && dayOfWeek <= 7)
			dayOfWeek_ = dayOfWeek;
		else
			return;
	}

	//=============================================================
	// METHOD : Returner dayOfWeek
	// DESCR. : 
	//=============================================================
	
	unsigned char getDayOfWeek()const
	{
		return dayOfWeek_;
	}
	
	//=============================================================
	// METHOD : Sætter action. 
	// DESCR. : 1 = Planlægges at skulle tændes. 
	//          0 = Planlægges at skulle slukkes.
	//=============================================================

	void setAction(bool action)
	{
		action_ = action;
	}

	//=============================================================
	// METHOD : Returner action
	// DESCR. : 
	//=============================================================

	bool getAction()const
	{
		return action_;
	}

	void print()const;

	friend istream& operator>>(istream& is, entry& obj);

private:
	unsigned char hour_;
	unsigned char min_;
	unsigned char dayOfWeek_;
	bool action_;
};


ostream& operator<<(ostream& os, const entry& obj);



//bool loadEntryData();
//bool storeEntry(entry&);


//=============================================================
// METHOD : 
// DESCR. : 
//=============================================================

//bool EnhedsRegister::loadEntryData()
//{
//	int h = 0x00, m = 0x00, d = 0x01; bool a = false;
//
//	in.open(outputFileEntry, ios::in);
//
//	if (!in)
//	{
//		cerr << "Filen findes ikke" << endl;
//		return false;
//	}
//
//	while (!in.eof())
//	{
//		in >> h >> m >> d >> a;
//		entryRegister_.push_back(entry(static_cast<unsigned char>(h), static_cast<unsigned char> (m), static_cast<unsigned char> (d), a));
//	}
//	in.close();
//	return true;
//}
//
//bool EnhedsRegister::storeEntry(entry&)
//{
//
//}

//vector<entry>entryRegister

//string outputFileEntry;