#include "nsbxcf.h"
#include "EditorTab.h"
#include "Controls/Entries/Tab.h"
#include <stdarg.h>

using namespace std;
using namespace bxcf;
using namespace imgf;

EditorTab::EditorTab(void) :
	m_pEditor(nullptr),
	m_pTab(nullptr),
	m_pFile(nullptr)
{
}

// tab index
uint32						EditorTab::getTabIndex(void)
{
	return m_pTab->getIndex();
}

// log
void						EditorTab::log(string strText)
{
}

void						EditorTab::logf(string strFormatText, ...)
{
	char szBuffer[8192];
	memset(szBuffer, '\0', 8192);
	va_list va;
	va_start(va, strFormatText);
	vsprintf_s(szBuffer, 8192, strFormatText.c_str(), va);
	va_end(va);
	log(szBuffer);
}