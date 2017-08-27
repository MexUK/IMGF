#pragma once

#include "Type/Types.h"
#include "nsimgf.h"

class imgf::CSortMenuItem
{
public:
	CSortMenuItem(uint32 uiMenuHandle, CSortPriority* pPriority, CSortType* pType);

	void				unload(void) {}

	uint32				m_uiMenuHandle;
	CSortPriority*		m_pPriority;
	CSortType*			m_pType;
};