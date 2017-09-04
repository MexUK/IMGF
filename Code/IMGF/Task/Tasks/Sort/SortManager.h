#pragma once

#include "nsimgf.h"
#include "nsbxcf.h"
#include "nsbxgi.h"
#include "Object/Manager.h"
#include <string>
#include <vector>

class bxgi::IMGFormat;
class bxgi::IMGEntry;
class imgf::SortPriority;
class imgf::SortType;
class imgf::SortTypes;
class imgf::SortPriorities;
class imgf::SortMenuItems;
class imgf::SortMenuItem;

class imgf::SortManager : public bxcf::Manager
{
public:
	SortManager(void);
	~SortManager(void);

	void									init(void);
	void									uninit(void);

	void									sort(bxgi::IMGFormat *pIMGFile);

	SortTypes*								getSortTypes(void) { return m_pSortTypes; }
	SortPriorities*						getSortPriorities(void) { return m_pSortPriorities; }
	SortMenuItems*							getSortMenuItems(void) { return m_pSortMenuItems; }

	void									setMenuPriorityTypesUnchecked(SortPriority *pSortPriority);
	void									setMenuPriorityTypeChecked(SortPriority *pSortPriority, SortType *pSortType, bool bState);

	bool									isMenuHandleUsed(uint16 usMenuHandle);
	void									onClickMenuItem(uint16 usMenuHandle);

private:
	static bool								sortIMGEntries(bxgi::IMGEntry *p1, bxgi::IMGEntry *p2);

	SortTypes*								m_pSortTypes;
	SortPriorities*						m_pSortPriorities;
	SortMenuItems*							m_pSortMenuItems;

	void									initSortTypes(void);
	void									uninitSortTypes(void);

	void									initSortPriorities(void);
	void									uninitSortPriorities(void);

	uint32							m_uiSortPriorityIndex;
	std::vector<SortMenuItem*>				m_vecSortMenuItems;
};