#include "LSTSection.h"
#include "LSTEntry.h"
#include "Static/String.h"

using namespace std;
using namespace bxcf;
using namespace imgf;

void					LSTSection::unload(void)
{
	removeAllEntries();
}

LSTEntry*				LSTSection::getEntryByName(string strName)
{
	strName = String::toUpperCase(strName);
	for (LSTEntry *pLSTEntry : m_vecEntries)
	{
		if (String::toUpperCase(pLSTEntry->getName()) == strName)
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