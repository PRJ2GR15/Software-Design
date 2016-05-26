//========================================================================
// FILENAME : <CommInterface.h>
// CREATED : <18/05-2016>
// AUTHOR : <Nikolai James Topping>
// DESCR. : <Header filen for MainMenu>
//
//------------------------------------------------------------------------
//
// REV. DATE/AUTHOR CHANGE DESCRIPTION
// 1.0 <18-05/2016/Nikolai J. Topping> <Oprettet fil. Tilføjet placeholder getUnitStatus funktion>
//========================================================================
#ifndef COMMINTERFACE_H
#define COMMINTERFACE_H
#pragma comment(lib, "SerialCom.lib")
#include "unit.h"
#include "SerialCom.h"
#include "UnitRegister.h"

class CommInterface
{
public:
    CommInterface() {
    }

    bool openComPort(int port, int baud, int dataBit, int paritet, int stopBit);
    void closeComPort();
    void sendCommand(char* cmd, int cmdSize);
    int readInputBuffer();
    bool PCConnected();
    void PCDisconnected();
    bool validatePin();
    //bool getUnitStatus(unsigned char unitID);
    void getAllUnits();
    bool deleteUnit(unsigned char unitID);
    //bool editUnit(unsigned char prevUnitID, unsigned char newUnitID);

    void setRegPtr(UnitRegister& regRef) { unitRegPtr = &regRef; }

    /*Unit getUnit() {
    }*/

    //Placeholder
    bool getUnitStatus(unsigned char ID) { return true; }

    //Placeholder
    void updateUnit(unsigned char previousID, unsigned char newID, unsigned char roomID);
protected:
    bool portOpened;
    UnitRegister* unitRegPtr;
private:
    //int a;
    SerialCom serialCom;
};

#endif // COMMINTERFACE_H
