#include "EnhedsRegister.h"

int main()
{
	unsigned char c = 0x00;
	EnhedsRegister m_register;
	m_register.getStoredUnits();
	
	vector<unit>::iterator iter = m_register.begin();
	for (iter = m_register.begin(); iter != m_register.end(); ++iter)
	{
		m_register.updateStatus(iter->getUnitID(), true);
	}

	m_register.getStoredUnits();
	 
		
	////for (int i = 0; i <= 20; ++i)
	//{
	//	c++;
	//	if (!m_register.storeUnit(unit(c, 0x00, ,false, 0)))
	//		cout << "Failed to add unit" << endl;
	//}
	/*ofstream f("test.txt");
	ostream_iterator<unit> oiter(f, "\n");
	copy(testVector.begin(), testVector.end(), oiter);*/



}