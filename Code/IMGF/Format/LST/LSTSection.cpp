#include "LSTSection.h"
#include "LSTEntry.h"
#include "Static/CString2.h"

using namespace std;
using namespace bxcf;
using namespace imgf;

void					LSTSection::unload(void)
{
	removeAllEntries();
}

LSTEntry*				LSTSection::getEntryByName(string strName)
{
	strName = CString2::toUpperCase(strName);
	for (LSTEntry *pLSTEntry : m_vecEntries)
	{
		if (CString2::toUpperCase(pLSTEntry->getName()) == strName)
		{
			return pLSTEntry;
		}
	}
	return nullptr;
}

bool					LSTSection::doesEntryExistByName(string strName)
{
	return getEntryByName(strName) != nullptr;
}