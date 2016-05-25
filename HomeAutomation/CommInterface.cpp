#include "CommInterface.h"

bool CommInterface::updateUnit(unsigned char previousID, unsigned char newID, unsigned char roomID) {
    return true;
}

void CommInterface::openComPort(int port, int baud, int dataBit, int paritet, int stopBit) {
    //Parity: 0 = PARITY_NONE, 1 = PARITY_ODD, 2 = PARITY_EVEN
    try
    {
        //serialCom.open(port, baud, dataBit, paritet, stopBit);
        serialCom.open(3, 9600, 8, PARITY_EVEN, 1);
    }
    catch (const char *e)
    {
        cout << e << endl;
        exit(1);
    }
    cout << "Serial Port: " << 3 << " Open." << endl;
}

void CommInterface::closeComPort() {
    try
    {
        serialCom.close();
    }
    catch(const char *e)
    {
        cout << e << endl;
        exit(1);
    }
    cout << "Serial port closed" << endl;
}

void CommInterface::sendCommand(char *cmd, int cmdSize) {
    try
    {
        serialCom.send(cmd, cmdSize);
    }
    catch(const char *e)
    {
        cout << e << endl;
        exit(1);
    }
    cout << "Data sent" << endl;
}

void CommInterface::readInputBuffer() {
    try
    {
        cout << "Before while loop... CommInterface::readInputBuffer" << endl;
        cout << serialCom.inWatingBuffer() << endl;
        /*while (serialCom.inWatingBuffer() != 0)
        {
            cout << "In while loop.. CommInterface::readInputBuffer" << endl;
            //unsigned char myChar = serialCom.receiveOneChar();
            cout << +serialCom.receiveOneChar() << ", ";
        }
        cout << endl;*/
    }
    catch (const char *e)
    {
        cout << e << endl;
        exit(1);
    }
}
