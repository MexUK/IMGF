#ifndef CTabBarControl_H
#define CTabBarControl_H

#include "Type/Types.h"
#include "Control/CGUIControl.h"
#include "Controls/Entries/CTabBarControlEntry.h"
#include <string>
#include <unordered_map>

class CGUILayer;

class CTabBarControl : public CGUIControl, public bxcf::CVectorPool<CTabBarControlEntry*>
{
public:
	CTabBarControl(void);

	void									bindEvents(void);

	void									unserialize(bool bSkipControlId = false);
	void									serialize(void);

	bool									onLeftMouseDown(bxcf::CPoint2D& vecCursorPosition);
	void									onRender(void);

	uint32									getActiveIndex(void);

	CTabBarControlEntry*					addTab(std::string strTabText, bool bSetActiveTab = false, std::string strStyleGroups = "");
	void									removeTab(CTabBarControlEntry *pTab);

	CTabBarControlEntry*					getTabFromPosition(bxcf::CPoint2D& vecPosition);

	void									bindTabLayer(CTabBarControlEntry *pTab, CGUILayer *pLayer);
	void									applyTabLayer(CTabBarControlEntry *pTab, CTabBarControlEntry *pPreviousTab);

	void									setActiveTab(CTabBarControlEntry* pActiveTab) { m_pActiveTab = pActiveTab; }
	CTabBarControlEntry*					getActiveTab(void) { return m_pActiveTab; }

	void									setActiveTabHeightDifference(uint32 uiActiveTabHeightDifference) { m_uiActiveTabHeightDifference = uiActiveTabHeightDifference; }
	uint32									getActiveTabHeightDifference(void) { return m_uiActiveTabHeightDifference; }

	void									setDefaultText(std::string strDefaultText) { m_strDefaultText = strDefaultText; }
	std::string								getDefaultText(void) { return m_strDefaultText; }

private:
	CTabBarControlEntry*									m_pActiveTab;
	uint32													m_uiActiveTabHeightDifference;
	std::string												m_strDefaultText;
	std::unordered_map<CTabBarControlEntry*, CGUILayer*>	m_umapTabLayers;
};

#endif