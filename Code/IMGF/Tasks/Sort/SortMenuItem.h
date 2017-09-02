#pragma once

#include "Type/Types.h"
#include "nsimgf.h"

class imgf::SortMenuItem
{
public:
	SortMenuItem(uint32 uiMenuHandle, SortPriority* pPriority, SortType* pType);

	void				unload(void) {}

	uint32				m_uiMenuHandle;
	SortPriority*		m_pPriority;
	SortType*			m_pType;
};