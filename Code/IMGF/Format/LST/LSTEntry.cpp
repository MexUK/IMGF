#include "LSTEntry.h"
#include "Static/CString2.h"

using namespace std;
using namespace bxcf;
using namespace imgf;

string					LSTEntry::getValue(uint32 uiValueIndex)
{
	return m_deqValues[uiValueIndex];
}

string					LSTEntry::getLine(void)
{
	return m_strName + " " + CString2::join(m_deqValues, " ");
}

string					LSTEntry::getValuesLine(void)
{
	return CString2::join(m_deqValues, " ");
}