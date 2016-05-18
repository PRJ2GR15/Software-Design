//========================================================================
// FILENAME : <EnhedsRegister.h>
// CREATED : <17/05-2016>
// AUTHOR : <Nikolai James Topping>
// DESCR. : <Header filen for EnhedsRegister>
//
//------------------------------------------------------------------------
//
// REV. DATE/AUTHOR CHANGE DESCRIPTION
// 1.0 <rev. date/author> <Change description>
// 1.1 <18.05/2016/Anders Brondbjerg Knudsen> <Tilføjelse af entry>
//========================================================================


#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include "unit.h"

using namespace std;

//=====================================
// CLASS : EnhedsRegister
// DESCR. : BLA BLA BLA
//=====================================


class EnhedsRegister
{
public:
	EnhedsRegister();
	~EnhedsRegister();
	bool storeUnit(unit&);
	bool updateStatus(char unitID, bool status);
	bool compareID(char unitID) const;
	void getStoredUnits();
	bool deleteUnit(char unitID);
	bool modifyUnit(char unitID, char roomID);
	//bool updateTime(char roomID, int placeholder);
	bool updateTime(char unitID, int placeholder);
	bool loadData();

private:
	vector<unit> unitRegister_;
	ofstream out;
	ifstream in;
	string outputFile;
	
};

istream& operator>>(istream&, const EnhedsRegister &);
