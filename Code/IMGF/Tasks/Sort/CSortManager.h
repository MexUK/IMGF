#ifndef CSortManager_H
#define CSortManager_H

#include "bxcf.h"
#include "bxgi.h"
#include "Object/CManager.h"
#include <string>
#include <vector>

class bxgi::CIMGFormat;
class bxgi::CIMGEntry;
class CSortPriority;
class CSortType;
class CSortTypes;
class CSortPriorities;
class CSortMenuItems;
class CSortMenuItem;

class CSortManager : public bxcf::CManager
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

#endif