#include "SortType.h"
#include "Static/String.h"

using namespace std;
using namespace bxcf;
using namespace imgf;

string					SortType::getText(void)
{
	return String::replace(m_strText, "&", "");
}

string					SortType::getTextForMenu(void)
{
	return m_strText;
}