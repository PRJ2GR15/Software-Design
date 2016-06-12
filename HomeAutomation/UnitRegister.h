//========================================================================
// FILENAME : <UnitRegister.h>
// CREATED : <17/05-2016>
// AUTHOR : <Nikolai James Topping>
// DESCR. : <Header filen for UnitRegister>
//
//------------------------------------------------------------------------
// REV. DATE/AUTHOR CHANGE DESCRIPTION
// 1.0 <18.05/2016/Nikolai J. Topping> <Tilføjet data fra QT projekt>
// 1.1 <20.05/2016/Nikolai J. Topping> <Entryregister ændres til at hedde UnitRegister>
// 1.1 <19.05/2016/Nikolai J. Topping> <Migreret inhold fra QT projekt>
// 1.2 <21/05-2016/Anders Brondbjerg Knudsen <Tilføjet addNewTime og upDate time>
//========================================================================
#ifndef UNITREGISTER_H
#define UNITREGISTER_H

#include <string>
#include <functional>
#include <QtCore>
#include "Unit.h"

using namespace std;

//=====================================
// CLASS : UnitRegister
// DESCR. : Håndterer lagring og manipulation af enheder
//=====================================
class UnitRegister
{
public:
    UnitRegister();
    bool storeUnit(Unit&);
    bool compareID(uchar unitID) const;
    bool deleteUnit(uchar unitID);
    bool modifyUnit(uchar originalUnitID, uchar unitID, uchar roomID);
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
#endif
