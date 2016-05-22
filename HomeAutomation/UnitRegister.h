//========================================================================
// FILENAME : <UnitRegister.h>
// CREATED : <17/05-2016>
// AUTHOR : <Nikolai James Topping>
// DESCR. : <Header filen for UnitRegister>
//
//------------------------------------------------------------------------
//
// REV. DATE/AUTHOR CHANGE DESCRIPTION
// 1.0 <17-05/2016/Nikolai J. Topping> <Oprettet fil.>
// 1.1 <18.05/2016/Anders Brondbjerg Knudsen> <Tilf�jelse af entry>
// 1.2 <19.05/2016/Nikolai J. Topping> <Migreret inhold fra QT projekt>
//========================================================================
#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <functional>
#include <QtCore>
#include "Unit.h"

using namespace std;

//=====================================
// CLASS : UnitRegister
// DESCR. : BLA BLA BLA
//=====================================
class UnitRegister
{
public:
    UnitRegister();
    ~UnitRegister();
    bool storeUnit(Unit&);
    bool compareID(uchar unitID) const;
    void getStoredUnits();
    bool deleteUnit(uchar unitID);
    bool modifyUnit(uchar unitID, uchar roomID);
    //bool updateTime(uchar roomID, int placeholder);
    bool updateTime(uchar unitID, int placeholder);
    bool loadData();

    void updateStates(function<bool(uchar)> f) {
        for(const auto& Unit: unitRegister_)
        {
            updateStatus( Unit.getUnitID(), f(Unit.getUnitID()) );
        }
    }
    bool updateStatus(uchar unitID, bool status);

    int getRegistrySize() {
        return unitRegister_.size();
    }

    vector<Unit>::iterator begin()
    {
        return unitRegister_.begin();
    }

    vector<Unit>::iterator end()
    {
        return unitRegister_.end();
    }

private:
    vector<Unit> unitRegister_;
    ofstream out;
    ifstream in;
    //string outputFile;

};

istream& operator>>(istream&, const UnitRegister &);
