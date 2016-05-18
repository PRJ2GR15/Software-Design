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
#include <vector>
#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include "unit.h"

using namespace std;

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
