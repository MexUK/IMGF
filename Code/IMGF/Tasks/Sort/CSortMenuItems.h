#pragma once

#include "nsimgf.h"
#include "CSortMenuItem.h"

class imgf::CSortMenuItems : public bxcf::CVectorPool<CSortMenuItem*>
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