#include "CLSTEntry.h"
#include "Type/String/CString2.h"

using namespace std;
using namespace mcore;

string					CLSTEntry::getValue(uint32 uiValueIndex)
{
	return m_deqValues[uiValueIndex];
}

string					CLSTEntry::getLine(void)
{
	return m_strName + " " + CString2::join(m_deqValues, " ");
}

string					CLSTEntry::getValuesLine(void)
{
	return CString2::join(m_deqValues, " ");
}