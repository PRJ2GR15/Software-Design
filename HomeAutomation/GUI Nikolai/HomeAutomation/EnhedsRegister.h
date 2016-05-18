#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <functional>
#include "unit.h"
#include <QtCore>

using namespace std;

class EnhedsRegister
{
public:
	EnhedsRegister();
	~EnhedsRegister();
	bool storeUnit(unit&);
    void updateStates(function<bool(uchar)> f) {
        for(const auto& unit: unitRegister_)
        {
            updateStatus( unit.getUnitID(), f(unit.getUnitID()) );
        }
    }

    bool updateStatus(uchar unitID, bool status);
    bool compareID(uchar unitID) const;
	void getStoredUnits();
    bool deleteUnit(uchar unitID);
    bool modifyUnit(uchar unitID, uchar roomID);
    //bool updateTime(uchar roomID, int placeholder);
    bool updateTime(uchar unitID, int placeholder);
	bool loadData();
    int getRegistrySize() {
        return unitRegister_.size();
    }

	vector<unit>::iterator begin()
	{
		return unitRegister_.begin();
	}

	vector<unit>::iterator end()
	{
		return unitRegister_.end();
	}

private:
	vector<unit> unitRegister_;
	ofstream out;
    ifstream in;
    //string outputFile;
};

istream& operator>>(istream&, const EnhedsRegister &);
