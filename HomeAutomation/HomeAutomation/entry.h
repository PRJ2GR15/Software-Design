#pragma once

class entry
{
public: //Constructor
	entry(unsigned char hour, unsigned char min, unsigned char dayOfWeek, bool action)
	{
		setHour(hour);
		setMin(min);
		setDayOfWeek(dayOfWeek);
		setAction(action);
	}
	//Metode for at sætte hour. Tilladte værdier 0-24
	void setHour(unsigned char hour)
	{
		if (hour >= 0 && hour <= 24)
			hour_ = hour;
		else
			return;
	}
	//Metode for at returner hour
	unsigned char getHour()const
	{
		return hour_;
	}

	//Metode for at sætte min. Tilladte værdier 0-59
	void setMin(unsigned char min)
	{
		if (min >= 0 && min <= 59)
			min_ = min;
		else
			return;
	}
	//Metode for at returner min
	unsigned char getMin()const
	{
		return min_;
	}
	//Metode for at sætte hour. Tilladte værdier 1-7
	void setDayOfWeek(unsigned char dayOfWeek)
	{
		if (dayOfWeek >= 1 && dayOfWeek <= 7)
			dayOfWeek_ = dayOfWeek;
		else
			return;
	}
	//Metode for at returner dayOfWeek
	unsigned char getDayOfWeek()const
	{
		return dayOfWeek_;
	}
	//Metode for at sætte action. 1 = Tænd. 0 = sluk
	void setAction(bool action)
	{
		action_ = action;
	}

	//Metode for at returner action
	bool getAction()const
	{
		return action_;
	}

private:
	unsigned char hour_;
	unsigned char min_;
	unsigned char dayOfWeek_;
	bool action_;
};
