#ifndef CSortMenuItems_H
#define CSortMenuItems_H

#include "CSortMenuItem.h"

class CSortMenuItems : public mcore::CVectorPool<CSortMenuItem*>
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

#endif