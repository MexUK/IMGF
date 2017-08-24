#include "CLSTSection.h"
#include "CLSTEntry.h"
#include "Static/CString2.h"

using namespace std;
using namespace bxcf;

void					CLSTSection::unload(void)
{
	removeAllEntries();
}

CLSTEntry*				CLSTSection::getEntryByName(string strName)
{
	strName = CString2::toUpperCase(strName);
	for (CLSTEntry *pLSTEntry : m_vecEntries)
	{
		if (CString2::toUpperCase(pLSTEntry->getName()) == strName)
		{
			return pLSTEntry;
		}
	}
	return nullptr;
}

bool					CLSTSection::doesEntryExistByName(string strName)
{
	return getEntryByName(strName) != nullptr;
}