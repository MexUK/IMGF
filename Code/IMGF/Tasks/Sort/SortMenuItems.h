#pragma once

#include "nsimgf.h"
#include "SortMenuItem.h"

class imgf::SortMenuItems : public bxcf::CVectorPool<SortMenuItem*>
{
public:
	SortMenuItem*	getEntryByMenuHandle(uint32 uiMenuHandle)
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