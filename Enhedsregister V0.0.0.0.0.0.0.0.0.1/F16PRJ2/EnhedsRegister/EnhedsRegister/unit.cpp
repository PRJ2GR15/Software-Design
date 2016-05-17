#include "unit.h"

std::ostream& operator<<(std::ostream& os, const unit& obj)
{
	return os
		<< obj.getUnitID()	<< " "
		<< obj.getRoomID()	<< " "
		<< obj.getStatus()	<< " "
		<< obj.getTime()	<< " ";
}

std::istream& operator>>(std::istream& is, unit& obj)
{
	is >> obj.unitID_;
	is >> obj.roomID_;
	is >> obj.status_;
	is >> obj.placeholderTime_;
	return is;
}
