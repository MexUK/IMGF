#include "LSTEntry.h"
#include "Static/String.h"

using namespace std;
using namespace bxcf;
using namespace imgf;

string					LSTEntry::getValue(uint32 uiValueIndex)
{
	return m_deqValues[uiValueIndex];
}

string					LSTEntry::getLine(void)
{
	return m_strName + " " + String::join(m_deqValues, " ");
}

string					LSTEntry::getValuesLine(void)
{
	return String::join(m_deqValues, " ");
}