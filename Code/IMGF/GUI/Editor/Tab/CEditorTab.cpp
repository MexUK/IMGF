#include "bxcf.h"
#include "CEditorTab.h"
#include <stdarg.h>

using namespace std;
using namespace bxcf;

CEditorTab::CEditorTab(void) :
	m_pEditor(nullptr),
	m_uiIndex(0),
	m_pFormat(nullptr)
{
}

// log
void						CEditorTab::log(string strText)
{
}

void						CEditorTab::logf(string strFormatText, ...)
{
	char szBuffer[8192];
	va_list va;
	va_start(va, strFormatText);
	vsprintf_s(szBuffer, strFormatText.c_str(), va);
	va_end(va);
	log(szBuffer);
}