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


#include "entry.h"

//=============================================================
// METHOD : 
// DESCR. : 
//=============================================================

void entry::print()const
{
	cout << +hour_ << " " << +min_ << " " << +dayOfWeek_ << " " << action_ << endl;
}

//=============================================================
// METHOD : 
// DESCR. : 
//=============================================================

ostream &operator<<(ostream& os, const entry& obj)
{
	obj.print();

	return os;
}

