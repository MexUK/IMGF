#include "CSortType.h"
#include "Type/String/CString2.h"

using namespace std;
using namespace mcore;

string					CSortType::getText(void)
{
	return CString2::replace(m_strText, "&", "");
}

string					CSortType::getTextForMenu(void)
{
	return m_strText;
}