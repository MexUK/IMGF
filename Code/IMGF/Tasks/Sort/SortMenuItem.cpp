#include "SortMenuItem.h"

using namespace imgf;

SortMenuItem::SortMenuItem(uint32 uiMenuHandle, SortPriority* pPriority, SortType* pType) :
	m_uiMenuHandle(uiMenuHandle),
	m_pPriority(pPriority),
	m_pType(pType)
{
}