//========================================================================
// FILENAME : <CommInterface.cpp>
// CREATED : <18/05-2016>
// AUTHOR : <Nikolai James Topping>
// DESCR. : <Implementering af CommInterface>
//
//------------------------------------------------------------------------
//
// REV. DATE/AUTHOR CHANGE DESCRIPTION
// 1.0 <18-05/2016/Nikolai J. Topping> <Oprettet fil. Tilføjet placeholder getUnitStatus funktion>
// 1.1 <24-05/2016/Nikolai J. Topping> <Tilføjet SerialCom bibliotek. Tilføjet begyndende kommunikation>
//========================================================================
#include "CommInterface.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>

bool CommInterface::updateUnit(unsigned char previousID, unsigned char newID, unsigned char roomID) {
    return true;
}

bool CommInterface::openComPort(int port, int baud, int dataBit, int paritet, int stopBit) {
    //Parity: 0 = PARITY_NONE, 1 = PARITY_ODD, 2 = PARITY_EVEN
    try
    {
        //serialCom.open(port, baud, dataBit, paritet, stopBit);
        serialCom.open(3, 9600, 8, PARITY_EVEN, 1);

    }
    catch (const char *e)
    {
        cout << e << endl;
        portOpened = false;
        return false;
    }
    cout << "Serial Port: " << 3 << " Open." << endl;
    portOpened = true;
    return true;
}

void CommInterface::closeComPort() {
    try
    {
        serialCom.close();
    }
    catch(const char *e)
    {
        cout << e << endl;
    }
    cout << "Serial port closed" << endl;
    portOpened = false;
}

void CommInterface::sendCommand(char *cmd, int cmdSize) {
    try
    {
        serialCom.send(cmd, cmdSize);
    }
    catch(const char *e)
    {
        cout << e << endl;
        return;
        //exit(1);
    }
}

int CommInterface::readInputBuffer() {
    int bytesRead = 0;
    try
    {   if(portOpened)
        {
            //Ja... Sleep. Puha - Giver lige arduinoen en chance for at svare tilbage.
            //Sleep i 100ms
            _sleep(150);
            if(serialCom.inWatingBuffer() == 0)
            {
                cout << "Der er ikke noget data at finde. CommInterface::readInputBuffer" << endl;
                ofstream output;
                output.open("serialData.txt", ios::out | ios::trunc);
                if(!output)
                {
                    cout << "Noget gik galt. CommInterface::readInputBuffer" << endl;
                    return bytesRead;
                }
                    output << 0;
                output.close();
                return bytesRead;
            }
            else {
                ofstream output;
                output.open("serialData.txt", ios::out | ios::trunc);
                if(!output)
                {
                    cout << "Noget gik galt. CommInterface::readInputBuffer" << endl;
                    return bytesRead;
                }
                while(serialCom.inWatingBuffer())
                {
                    //cout << "Current amount of data in input buffer: " << serialCom.inWatingBuffer() << endl;
                    output << +serialCom.receiveOneChar() << " ";
                    bytesRead++;
                }
                output.close();
                return bytesRead;
            }

        }
    }
    catch (const char *e)
    {
        cout << e << endl;
        //exit(1);
    }
}

bool CommInterface::PCConnected()
{
    //Sender PC Tilsluttet kommando
    const int cmdSize = 5;
    char cmd[cmdSize] = {0xF0, 0xF0, 0x01, 0x0F, 0x0F};
    sendCommand(cmd, cmdSize);
    readInputBuffer();
    ifstream input;
    input.open("serialData.txt", ios::in);
    if(!input)
    {
        cout << "Noget gik galt. CommInterface::PCConnected" << endl;
        return false;
    }
    //Forventet svar fra PC Tilsluttet kommando = 1 byte.
    int reply;
    input >> reply;
    input.close();
    cout << reply << endl;
    if(reply == 0x0F)
        return true;
    else
        return false;

}
void CommInterface::PCDisconnected()
{
    //Sender PC Frakoblet kommando
    const int cmdSize = 5;
    char cmd[cmdSize] = {0xF0, 0xF0, 0x02, 0x0F, 0x0F};
    sendCommand(cmd, cmdSize);
    readInputBuffer();
    ifstream input;
    input.open("serialData.txt", ios::in);
    if(!input)
    {
        cout << "Noget gik galt. CommInterface::PCDisconnected" << endl;
        return;
    }
    //Forventet svar fra PC Frakoblet kommando = 1 byte.
    int reply;
    input >> reply;
    input.close();
    //cout << "Reply fra PC Frakoblet" << endl << "Forventet: 15" << endl << "Modtaget: " << reply << endl;
}
bool CommInterface::validatePin() {
    //Sender valider(check om pin er indtastet)pin kommando
    const int cmdSize = 5;
    char cmd[cmdSize] = {0xF0, 0xF0, 0x03, 0x0F, 0x0F};
    sendCommand(cmd, cmdSize);
    readInputBuffer();
    ifstream input;
    input.open("serialData.txt", ios::in);
    if(!input)
    {
        cout << "Noget gik galt. CommInterface::PCDisconnected" << endl;
        return false;
    }
    //Forventet svar fra valider(check om pin er indtastet)pin kommando = 1 byte.
    int reply;
    input >> reply;
    input.close();
    cout << "Output fra Validate pin: " << reply << endl;
    if(reply == 0x01)
        return true;
    else
        return false;
}
bool CommInterface::getUnitStatus(unsigned char unitID)
{
    //Sender hent unit status kommando
    const int cmdSize = 6;
    char cmd[cmdSize] = {0xF0, 0xF0, 0x05, unitID, 0x0F, 0x0F};
    cout << "Opdaterer UnitID: " << +cmd[3] << endl;
    sendCommand(cmd, cmdSize);
    readInputBuffer();
    ifstream input;
    input.open("serialData.txt", ios::in);
    if(!input)
    {
        cout << "Noget gik galt. CommInterface::PCDisconnected" << endl;
        return false;
    }
    //Forventet svar fra valider(check om pin er indtastet)pin kommando = 1 byte.
    int reply;
    input >> reply;
    input.close();
    if(reply == 0x01)
    {
        cout << "Status på UnitID: " << +cmd[3] << " TRUE" << endl;
        return true;
    }
    else
    {
        cout << "Status på UnitID: " << +cmd[3] << " FALSE" << endl;
        return false;
    }
}
void CommInterface::getAllUnits()
{
    //Forventet svar tilbage: 512 * 7 bytes. 3584 bytes. Per Unit.
    //Data gemmes i format:
    /*
    Byte 0: Unit ID, Byte 1: Don't Care, Byte 2: Room ID, Byte 3: Dag(0, 1, 2... 6) (mandag, tirsdag...), Byte 4: Entry ID, Byte 5: Time, Byte 6: Minut, Byte 7: Handling.
    Byte 3 bestemmer dagen hvor enheden skal gemmes på den pågældende unit. 4 efterfølgende bytes er ÉT entry. Hvis Entry ID = 0x00 er der ingen/ikke flere entries.
    Der skal altid hentes 512 bytes.
    HVIS: Byte 0, Byte 1, Byte 2 og Byte 3 alle = 0xFA, så er der ikke flere enheder at hente
    */
    Unit tmpUnit(1,1,0,1);
    //Sender hent unit status kommando
    const int arraySize = 8;
    int byteCounter = 0;
    int byteArray[arraySize];
    int day;
    const int cmdSize = 5;
    char cmd[cmdSize] = {0xF0, 0xF0, 0x06, 0x0F, 0x0F};
    sendCommand(cmd, cmdSize);
    int bytesToProcess = readInputBuffer();
    ifstream input;
    input.open("serielData.txt", ios::in);
    if(!input)
    {
        cout << "Noget gik galt. CommInterface::getAllUnits" << endl;
        return;
    }
    while(!input.eof())
    {
        if(bytesToProcess <= 4)
            //DER ER EN FEJL. STOP HER.
            return;

        //Hvis jeg har talt til 511, så må jeg have kørt den første blok data igennem. Den næste blok der kommer
        //Hører derfor til
        if(byteCounter >= 511)
        {

        }

        int errCount = 0;
        for(int i = 0; i < arraySize || input.eof(); i++) {
            input >> byteArray[i];
            byteCounter++;
        }

        /*for(int i = 0; i < 4; i++) {
            if(byteArray[i] == 0xFA)
                errCount++;
            if(errCount >= 4)
            {
                errCount = 0;
                //RETURN OG GÅ UD AF LOOP. NOGET. DER ER IKKE FLERE ENHEDER.
                return Unit(0,0,0,0);
            }
        }*/

        //Hvis man har fat i de første 8 bytes, hvor Unit ID indgår
        if(byteCounter <= 7)
        {
            tmpUnit.setUnitID(byteArray[0]);
            tmpUnit.setRoomID(byteArray[2]);
            day = byteArray[3];
            //Hvis entryID er == 0x00, er der ingen entries at tilføje.
            if(byteArray[4] == 0x00)
                return tmpUnit;
            tmpUnit.storeEntry(day,Entry(byteArray[4], byteArray[5], byteArray[6], byteArray[7]));
        }
        //Nu er vi i vildmarken. Vi er forbi de første 8 bytes, og nu skal resten af de uendelige bytes behandles.
        //Efter byte 7, læses de næste 8 bytes fra filen ind i byteArray, mønstret vil være som følgende:
        //Byte 0: Entry ID, Byte 1: Time, Byte 2: Minut, Byte 3: Handling, Byte 4: Entry ID, Byte 5: Time, Byte 6: Minut, Byte 7: Handling
        //Hvis et Entry ID == 0x00 er der ikke flere entries at arbejde med, og de tilbageværende bytes ud af de 512 er skrald.
        //Under er en sloppy løsning til at lade som om mit array med 8 bytes, i virkeligheden er 2 arrays med 4 bytes. Uden egentlig at lave et. Fordi.
        for(int i = 0; i < 2; i++) {
            if(byteArray[0+(4*i)] != 0x00)
            {
                tmpUnit.storeEntry(day,Entry(byteArray[0+(4*i)], byteArray[1+(4*i)], byteArray[2+(4*i)], byteArray[3+(4*i)]));
            }
        }
    }
}
