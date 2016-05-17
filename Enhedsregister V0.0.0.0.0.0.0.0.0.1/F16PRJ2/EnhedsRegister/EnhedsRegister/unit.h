#pragma once
#include <ostream>
#include <iostream>

class unit
{
public:
	unit(char unitID, char roomID, bool status, int time)
	{
		unitID_ = unitID;
		roomID_ = roomID;
		status_ = status;
		placeholderTime_ = time;
	}

	char getUnitID() const
	{
		return unitID_;
	}

	void setUnitID(char unitID)
	{
		unitID_ = unitID;
	}

	char getRoomID() const
	{
		return roomID_;
	}

	void setRoomID(char roomID)
	{
		roomID_ = roomID;
	}

	int getTime() const
	{
		return placeholderTime_;
	}

	void setTime(int placeholder_time)
	{
		placeholderTime_ = placeholder_time;
	}

	bool getStatus() const
	{
		return status_;
	}

	friend std::istream& operator>>(std::istream& is, unit& obj);

	void setStatus(bool newState)
	{
		status_ = newState;
	}
private:
	char unitID_;
	char roomID_;
	bool status_;
	int placeholderTime_;	
};

std::ostream& operator<<(std::ostream& os, const unit& obj);
