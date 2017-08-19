#include "CSortType.h"
#include "Static/CString2.h"

using namespace std;
using namespace bxcf;

string					CSortType::getText(void)
{
	return CString2::replace(m_strText, "&", "");
}

string					CSortType::getTextForMenu(void)
{
	return m_strText;
}