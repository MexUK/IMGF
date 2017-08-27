#include "CSortMenuItem.h"

using namespace imgf;

CSortMenuItem::CSortMenuItem(uint32 uiMenuHandle, CSortPriority* pPriority, CSortType* pType) :
	m_uiMenuHandle(uiMenuHandle),
	m_pPriority(pPriority),
	m_pType(pType)
{
}