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
// 1.2 <25-05/2016/Nikolai J. Topping> <Tilføjet sendCommand, readInputBuffer, PCConnected, PCDisconnected, validatePin, getAllUnits, editUit, deleteUnit>
//========================================================================
#include "CommInterface.h"
#include <iostream>
#include <QtWidgets>
#include <stdlib.h>
#include <fstream>


//=============================================================
// METHOD : openComPort
// DESCR. : Åbner COM port til UART kommunikation mellem PC og styreboks
//=============================================================
bool CommInterface::openComPort(int port, int baud, int dataBit, int paritet, int stopBit) {
    //Parity: 0 = PARITY_NONE, 1 = PARITY_ODD, 2 = PARITY_EVEN
    try
    {
        serialCom.open(port, baud, dataBit, paritet, stopBit);

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

//=============================================================
// METHOD : closeComPort
// DESCR. : Lukker COM porten
//=============================================================
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

//=============================================================
// METHOD : sendCommand
// DESCR. : Sender en kommando til styreboksen
//=============================================================
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

//=============================================================
// METHOD : readInputBuffer
// DESCR. : Læser input buffer til .txt fil
//=============================================================
int CommInterface::readInputBuffer() {
    int bytesRead = 0;
    try
    {   if(portOpened)
        {
            //Ja... Sleep. Puha - Giver lige arduinoen en chance for at svare tilbage.
            //Sleep i 100ms
            _sleep(100);
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
        return -1;
    }
    catch (const char *e)
    {
        cout << e << endl;
        //exit(1);
    }
}

//=============================================================
// METHOD : PCConnected
// DESCR. : Sender PC Connected kommando til styreboks
//=============================================================
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
    if(reply == 0x0F)
        return true;
    else
        return false;

}

//=============================================================
// METHOD : PCDisconnected
// DESCR. : Sender PC Disconnected kommando til styreboks
//=============================================================
void CommInterface::PCDisconnected()
{
    //Sender PC Frakoblet kommando
    const int cmdSize = 5;
    char cmd[cmdSize] = {0xF0, 0xF0, 0x02, 0x0F, 0x0F};
    sendCommand(cmd, cmdSize);
    if(readInputBuffer() == -1)
        return;
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
}

//=============================================================
// METHOD : validatePin
// DESCR. : Sender validate pin kommando til styreboks
//=============================================================
bool CommInterface::validatePin() {
    //Sender valider(check om pin er indtastet)pin kommando
    const int cmdSize = 5;
    char cmd[cmdSize] = {0xF0, 0xF0, 0x03, 0x0F, 0x0F};
    cout << "CommInterface::validatePin : sent command" << endl;
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
        return true;
    else
        return false;
}

//=============================================================
// METHOD : getUnitStatus
// DESCR. : Henter status på enhed ud fra ID, fra styreboksen
//=============================================================
bool CommInterface::getUnitStatus(unsigned char unitID)
{
    //Sender hent unit status kommando
    const int cmdSize = 6;
    char cmd[cmdSize] = {0xF0, 0xF0, 0x05, unitID, 0x0F, 0x0F};
    sendCommand(cmd, cmdSize);
    int replySize = readInputBuffer();
    if(replySize == 0)
    {
        cerr << "CommInterface::getUnitStatus - Intet svar fra opdater enhed. Returnerer false." << endl;
        return false;
    }
    ifstream input;
    input.open("serialData.txt", ios::in);
    if(!input)
    {
        cerr << "serialData.txt ikke åbnet - CommInterface::PCDisconnected" << endl;
        return false;
    }
    //Forventet svar fra get unit status kommando = 1 byte.
    int reply;
    input >> reply;
    input.close();
    if(reply == 0x01)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//=============================================================
// METHOD : getAllUnits
// DESCR. : Henter alle enheder fra styreboks og lagre i UnitRegister
//=============================================================
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
    int day = 0;
    const int cmdSize = 5;
    char cmd[cmdSize] = {0xF0, 0xF0, 0x06, 0x0F, 0x0F};
    sendCommand(cmd, 5);
    cout << "CommInterface::getAllUnits - Sent Command" << endl;
    //600 - Magic number. Skal nok ændres efter det er testet med SD-Kort
    _sleep(600);
    int bytesToProcess = readInputBuffer();

    if(bytesToProcess <= 3583)
    {
        cout << bytesToProcess << endl;
        return;
    }

    ifstream input;
    input.open("serialData.txt", ios::in);
    if(!input)
    {
        cout << "Noget gik galt. CommInterface::getAllUnits" << endl;
        return;
    }
    while(!input.eof())
    {
        for(int i = 0; i < arraySize; i++) {
            input >> byteArray[i];
            byteCounter++;
        }
        //Hvis man har fat i de første 8 bytes, hvor Unit ID indgår
        if(byteCounter <= 8)
        {
            tmpUnit.setUnitID(byteArray[0]);
            tmpUnit.setRoomID(byteArray[2]);
            //Hvis entryID er == 0x00, er der ingen entries at tilføje.
            if(byteArray[4] != 0x00)
                tmpUnit.storeEntry(day,Entry(byteArray[4], byteArray[5], byteArray[6], byteArray[7]));
        }
        else
        {
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
        //Når bytecounter når 512, har jeg læst og behandlet alt data fra ÉN dag. Derfor skal day counteren øges med 1.
        if(byteCounter >= 512)
        {
            byteCounter = 0;
            ++day;
            //Hvis dag er 7, så har jeg behandlet samtlige 7 * 512 blokke af data. Derfor er jeg nået enden af min serialData.txt fil.
            //Mit while loop vil derfor stoppe når jeg kommmer til enden, den enhed jeg har arbejdet med skal derfor gemmes i vores register, da jeg er færdig med den.
            if(day >= 7)
            {
                unitRegPtr->storeUnit(tmpUnit);
            }
        }
    }
    //Uden for while loopet nu, men jeg skal blive ved med at hente enheder op, indtil jeg får mine fire "error" bytes(0xFAFAFAFA). Derfor kalder jeg bare getAllUnits en gang til.
    getAllUnits();
}

//=============================================================
// METHOD : editUnit
// DESCR. : Sender EditUnit kommando til styreboks, med info vedr. ændringer til enhed
//=============================================================
bool CommInterface::editUnit(unsigned char previousID, unsigned char newID, unsigned char roomID) {
    //Sender Edit Unit kommando
    const int cmdSize = 8;
    char cmd[cmdSize] = {0xF0, 0xF0, 0x09, previousID, newID, roomID, 0x0F, 0x0F};
    sendCommand(cmd, cmdSize);
    int replySize = readInputBuffer();
    if(replySize == 1)
    {
        ifstream input;
        input.open("serialData.txt", ios::in);
        if(!input)
        {
            cerr << "Fil ikke åbnet. CommInterface::sendUnit" << endl;
            return false;
        }
        int reply;
        input >> reply;
        input.close();
        if(reply == 0x0F)
            return true;
        else
            return false;
    } else// if(replySize == 4)
    {
        cerr << "CommInterface::editUnit. Did not get approved command" << endl;
        return false;
    }
}

//=============================================================
// METHOD : deleteUnit
// DESCR. : Sender delete unit kommando til styreboksen
//=============================================================
bool CommInterface::deleteUnit(unsigned char unitID) {
    //Sender Delete Unit kommando
    const int cmdSize = 6;
    char cmd[cmdSize] = {0xF0, 0xF0, 0x08, unitID, 0x0F, 0x0F};
    sendCommand(cmd, cmdSize);
    int replySize = readInputBuffer();
    //Forventet svar: 1 Byte godkendt, 4 byte fejl.
    if(replySize == 1)
    {
        ifstream input;
        input.open("serialData.txt", ios::in);
        if(!input)
        {
            cerr << "Fil ikke åbnet. CommInterface::sendUnit" << endl;
            return false;
        }
        int reply;
        input >> reply;
        input.close();
        if(reply == 0x0F)
            return true;
        else
            return false;
    } else// if(replySize == 4)
    {
        cerr << "CommInterface::deleteUnit. Did not get approved command" << endl;
        return false;
    }
}

//=============================================================
// METHOD : sendUnit
// DESCR. : Sender en Unit til styreboksen
//=============================================================
bool CommInterface::sendUnit(unsigned char unitID, unsigned char roomID)
{
    //Kommando for at sende en enhed = 0xF0F0 , 0x07 , unitID, roomID, 0x0F0F
    const int cmdSize = 7;
    char cmd[cmdSize] = {0xF0, 0xF0, 0x07, unitID, roomID, 0x0F, 0x0F};
    sendCommand(cmd, cmdSize);
    int replySize = readInputBuffer();
    //Forventet svar: 1 Byte godkendt, 4 byte fejl.
    if(replySize == 1)
    {
        ifstream input;
        input.open("serialData.txt", ios::in);
        if(!input)
        {
            cerr << "Fil ikke åbnet. CommInterface::sendUnit" << endl;
            return false;
        }
        int reply;
        input >> reply;
        input.close();
        if(reply == 0x0F)
            return true;
        else
            return false;
    } else// if(replySize == 4)
    {
        cerr << "CommInterface::sendUnit. Did not get approved command" << endl;
        return false;
    }

}

//=============================================================
// METHOD : readAckCommand
// DESCR. : Læser en ACK kommando fra styreboksen
//=============================================================
bool CommInterface::readAckCommand()
{
    int replySize = readInputBuffer();
    if(replySize != 0)
    {
        ifstream input;
        input.open("serialData.txt", ios::in);
        if(!input)
        {
            cerr << "Fil ikke åbnet. CommInterface::sendUnit" << endl;
            return false;
        }
        int reply;
        input >> reply;
        input.close();
        if(reply == 0x0F)
            return true;
        else
            return false;
    }
    else// if(replySize == 4)
    {
        cerr << "CommInterface::sendEntries. Did not get approved command" << endl;
        return false;
    }
}

//=============================================================
// METHOD : sendEntries
// DESCR. : Sender alle entries for en given Unit og en given dag til styreboksen
//=============================================================
bool CommInterface::sendEntries(Unit& obj, int day)
{
    unsigned char unitID = obj.getUnitID(); unsigned char roomID = obj.getRoomID();
    vector<vector<Entry> > entryRegPtr = obj.getEntryRegisterRef();
    char dataToSend[1] = {0x00};
    //Hvis der ingen entries er at sende.
    if(entryRegPtr[day].size() == 0)
    {
        //Send start kommando. Få et svar.
        const int cmdSize = 3;
        char cmd[cmdSize] = {0xF0, 0xF0, 0x0A};
        sendCommand(cmd, cmdSize);
        int replySize = readInputBuffer();
        if(replySize != 0)
        {
            ifstream input;
            input.open("serialData.txt", ios::in);
            if(!input)
            {
                cerr << "Fil ikke åbnet. CommInterface::sendUnit" << endl;
                return false;
            }
            int reply;
            input >> reply;
            input.close();
            if(reply != 0x0F)
                return false;
        }
        else// if(replySize == 4)
        {
            cerr << "CommInterface::sendEntries. Did not get approved command" << endl;
            return false;
        }
        //Nu sendes den "rigtige data"
        char noEntries[4] = {unitID, roomID, day, 0x00};
        for(int i = 0; i < 4; i++)
        {
            dataToSend[0] = noEntries[i];
            sendCommand(dataToSend, 1);
            replySize = readInputBuffer();
            if(!readAckCommand())
            {
                cerr << "CommInterface::sendEntries - ved ingen entries : ack command fejl" << endl;
                return false;
            }
        }
        //Stop delen af command.
        dataToSend[0] = 0x0F;
        sendCommand(dataToSend, 1); sendCommand(dataToSend, 1);
        return true;
    }
    else
    {
        const int cmdSize = 3;
        char cmd[cmdSize] = {0xF0, 0xF0, 0x0A};
        sendCommand(cmd, cmdSize);
        int replySize = readInputBuffer();
        //Hent og læs svaret
        if(!readAckCommand())
        {
            cerr << "CommInterface::sendEntries - ved nogen entries : ack command fejl" << endl;
            return false;
        }
        dataToSend[0] = day;
        if(!readAckCommand())
        {
            cerr << "CommInterface::sendEntries - ved nogen entries : send day ack command fejl" << endl;
            return false;
        }

        //SEND NOGEN F*****G ENTRIES.
        for(int i = 0; i < entryRegPtr[day].size(); i++)
        {
            dataToSend[0] = entryRegPtr[day][i].EntryID();
            sendCommand(dataToSend, 1);
            if(!readAckCommand())
            {
                cerr << "CommInterface::sendEntries - efter sendt EntryID : fejl" << endl;
                return false;
            }
            dataToSend[0] = entryRegPtr[day][i].getHour();
            sendCommand(dataToSend, 1);
            if(!readAckCommand())
            {
                cerr << "CommInterface::sendEntries - efter sendt time : fejl" << endl;
                return false;
            }
            dataToSend[0] = entryRegPtr[day][i].getMin();
            sendCommand(dataToSend, 1);
            if(!readAckCommand())
            {
                cerr << "CommInterface::sendEntries - efter sendt minut : fejl" << endl;
                return false;
            }
            dataToSend[0] = entryRegPtr[day][i].getAction();
            sendCommand(dataToSend, 1);
            if(!readAckCommand())
            {
                cerr << "CommInterface::sendEntries - efter sendt handling : fejl" << endl;
                return false;
            }
        }
        dataToSend[0] = 0x0F;
        sendCommand(dataToSend, 1); sendCommand(dataToSend, 1);
        return true;
    }
}
