#pragma once

#include "nsimgf.h"
#include "nsbxcf.h"
#include "nsbxgi.h"
#include "Object/CManager.h"
#include <string>
#include <vector>

class bxgi::CIMGFormat;
class bxgi::CIMGEntry;
class imgf::CSortPriority;
class imgf::CSortType;
class imgf::CSortTypes;
class imgf::CSortPriorities;
class imgf::CSortMenuItems;
class imgf::CSortMenuItem;

class imgf::CSortManager : public bxcf::CManager
{
public:
	CSortManager(void);
	~CSortManager(void);

	void									init(void);
	void									uninit(void);

	void									sort(bxgi::CIMGFormat *pIMGFile);

	CSortTypes*								getSortTypes(void) { return m_pSortTypes; }
	CSortPriorities*						getSortPriorities(void) { return m_pSortPriorities; }
	CSortMenuItems*							getSortMenuItems(void) { return m_pSortMenuItems; }

	void									setMenuPriorityTypesUnchecked(CSortPriority *pSortPriority);
	void									setMenuPriorityTypeChecked(CSortPriority *pSortPriority, CSortType *pSortType, bool bState);

	bool									isMenuHandleUsed(uint16 usMenuHandle);
	void									onClickMenuItem(uint16 usMenuHandle);

private:
	static bool								sortIMGEntries(bxgi::CIMGEntry *p1, bxgi::CIMGEntry *p2);

	CSortTypes*								m_pSortTypes;
	CSortPriorities*						m_pSortPriorities;
	CSortMenuItems*							m_pSortMenuItems;

	void									initSortTypes(void);
	void									uninitSortTypes(void);

	void									initSortPriorities(void);
	void									uninitSortPriorities(void);

	uint32							m_uiSortPriorityIndex;
	std::vector<CSortMenuItem*>				m_vecSortMenuItems;
};