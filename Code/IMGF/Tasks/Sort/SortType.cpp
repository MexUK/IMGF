#include "SortType.h"
#include "Static/String2.h"

using namespace std;
using namespace bxcf;
using namespace imgf;

string					SortType::getText(void)
{
	return String2::replace(m_strText, "&", "");
}

string					SortType::getTextForMenu(void)
{
	return m_strText;
}