#include "Unit.h"

int main()

{
	Entry test(20, 20, 0);
	Entry test2(21, 21, 1);
	Entry test3(23, 45, 1);
	Entry test4(23, 45, 1);
	Unit unit1(256, 2, 2, 0);

	unit1.storeEntry(0, test);
	unit1.storeEntry(1, test2);
	unit1.storeEntry(2, test3);
	unit1.storeEntry(2, test4);
	cout << unit1 << endl;

	Unit unit2(2, 2, 2, 1);

	unit2.storeEntry(2,test4);

	cout << unit2;
}