// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the SERIALCOM_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// SERIALCOM_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef SERIALCOM_EXPORTS
#define SERIALCOM_API __declspec(dllexport)
#else
#define SERIALCOM_API __declspec(dllimport)
#endif

#include <Windows.h>
#include <exception>

/**
 * This class handle serial communication 
 */
class SERIALCOM_API SerialCom {
public:
	/**
	 * An enum to be used in function SerialCom::getPorts.
	 * ALL, SERIAL, USB, BLUETOOTH
	 */
	enum porttype { ALL = 0, SERIAL = 1, USB = 2, BLUETOOTH = 4 };
	void open(int port, int baud, int dataBit, int paritet, int stopBit);
	void close();
	void send(char *sendPtr, int number);
	int inWatingBuffer();
	int receive(char *rxPtr, int maxNumber);
	char receiveOneChar();
	int *getPorts(SerialCom::porttype portType, int &size);
private:
	HANDLE _HComdev; //Def af handle til pc
	DWORD _dwErrorFlags;
	COMSTAT _ComStat;
	DCB _dcb; //Def af variabel til DCB structen
};
