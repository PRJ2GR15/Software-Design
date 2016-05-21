#include "Unit.h"

int main()

{
	Entry test(20, 20, 0);
	Entry test2(21, 21, 1);
	Entry test3(23, 45, 1);
	Entry test4(23, 45, 1);
	Unit unit1(5, 2, 2, 0);

	unit1.storeEntry(0, test);
	unit1.storeEntry(0, test2);
	unit1.storeEntry(2, test3);
	unit1.storeEntry(5, test4);
	unit1.storeEntry(6, test4);
	cout << unit1 << endl;

	unit1.clearData();

	unit1.storeEntryData();

	Unit unit2(3, 2, 2, 0);
	unit2.storeEntry(0, test);
	unit2.storeEntry(1, test2);

	unit2.storeEntryData();
	//unit1.storeEntryData();
	cout << unit2 << endl;

	
}