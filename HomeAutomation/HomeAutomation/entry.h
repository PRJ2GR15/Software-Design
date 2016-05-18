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

class entry
{
public: 

	//=============================================================
	// METHOD : 
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
	// METHOD : 
	// DESCR. : 
	//=============================================================

	void setHour(unsigned char hour)
	{
		if (hour >= 0 && hour <= 24)
			hour_ = hour;
		else
			return;
	}

	//=============================================================
	// METHOD : 
	// DESCR. : 
	//=============================================================

	unsigned char getHour()const
	{
		return hour_;
	}

	//=============================================================
	// METHOD : 
	// DESCR. : 
	//=============================================================

	void setMin(unsigned char min)
	{
		if (min >= 0 && min <= 59)
			min_ = min;
		else
			return;
	}
	
	//=============================================================
	// METHOD : 
	// DESCR. : 
	//=============================================================

	unsigned char getMin()const
	{
		return min_;
	}
	
	//=============================================================
	// METHOD : 
	// DESCR. : 
	//=============================================================

	void setDayOfWeek(unsigned char dayOfWeek)
	{
		if (dayOfWeek >= 1 && dayOfWeek <= 7)
			dayOfWeek_ = dayOfWeek;
		else
			return;
	}

	//=============================================================
	// METHOD : 
	// DESCR. : 
	//=============================================================
	
	unsigned char getDayOfWeek()const
	{
		return dayOfWeek_;
	}
	
	//=============================================================
	// METHOD : 
	// DESCR. : 
	//=============================================================

	void setAction(bool action)
	{
		action_ = action;
	}

	//=============================================================
	// METHOD : 
	// DESCR. : 
	//=============================================================

	bool getAction()const
	{
		return action_;
	}

	void print()const;

private:
	unsigned char hour_;
	unsigned char min_;
	unsigned char dayOfWeek_;
	bool action_;
};


ostream& operator<<(ostream& os, const entry& obj);