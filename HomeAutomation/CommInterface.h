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


class CommInterface
{
public:
    CommInterface() {
        int a = 0;
    }

    //Placeholder
    bool getUnitStatus(unsigned char ID) {
        return true;
    }
private:
    int a;
};

#endif // COMMINTERFACE_H
