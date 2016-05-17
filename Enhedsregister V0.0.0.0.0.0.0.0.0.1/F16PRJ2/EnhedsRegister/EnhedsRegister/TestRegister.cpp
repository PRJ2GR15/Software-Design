#include "EnhedsRegister.h"

int main()
{
	unsigned char c = 0x00;
	EnhedsRegister m_register;
/*	for (int i = 0; i <= 20; ++i)
	{
		c++;
		if (!m_register.storeUnit(unit(c, 0x00, false, 0)))
			cout << "Failed to add unit" << endl;
	}*/
	m_register.getStoredUnits();
	/*ofstream f("test.txt");
	ostream_iterator<unit> oiter(f, "\n");
	copy(testVector.begin(), testVector.end(), oiter);*/



}