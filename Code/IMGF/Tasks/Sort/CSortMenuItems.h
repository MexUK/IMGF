#pragma once

#include "CSortMenuItem.h"

class CSortMenuItems : public bxcf::CVectorPool<CSortMenuItem*>
{
public:
	CSortMenuItem*	getEntryByMenuHandle(uint32 uiMenuHandle)
	{
		for (auto pSortMenuItem : getEntries())
		{
			if (pSortMenuItem->m_uiMenuHandle == uiMenuHandle)
			{
				return pSortMenuItem;
			}
		}
		return nullptr;
	}
};