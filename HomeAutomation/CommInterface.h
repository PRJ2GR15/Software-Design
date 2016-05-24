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
#include "unit.h"
#include "Serial.h"

class CommInterface
{
public:
    CommInterface() {
        int a = 0;
    }

    Unit getUnit() {
        const int commandSize = 5;
        CSerial* s = new CSerial();
        //Get unit command = F0F0 06 0F0F
        unsigned char data[commandSize] = {0xF0, 0xF0, 0x06, 0x0F, 0x0F};
        if(!s->Open(3, 115000))
        {
            cout << "Could not open COM Port: " << port << endl;
            return;
        }
        s->SendData(data, commandSize);
        cout << "Data sent" << endl;
        s->Close();
        delete s;
    }

    //Placeholder
    bool getUnitStatus(unsigned char ID) { return true; }

    //Placeholder
    bool updateUnit(unsigned char previousID, unsigned char newID, unsigned char roomID);
private:
    int a;
};

#endif // COMMINTERFACE_H
