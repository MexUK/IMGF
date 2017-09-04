#pragma once

#include "nsbxgx.h"
#include "Type/Types.h"
#include "Control/Control.h"
#include "Controls/Entries/CTab.h"
#include "Event/Events.h"
#include <string>
#include <unordered_map>

class bxgx::CLayer;

class bxgx::CTabBar : public bxgx::Control, public bxcf::CVectorPool<CTab*>
{
public:
	CTabBar(void);

	void									bindEvents(void);

	void									unserialize(bool bSkipControlId = false);
	void									serialize(void);

	bool									onLeftMouseUp(bxcf::Vec2i& vecCursorPosition);
	bool									onMouseMove(bxcf::Vec2i& vecCursorPosition);
	bool									onMouseEnter(bxcf::Vec2i& vecCursorPosition);
	bool									onMouseExit(bxcf::Vec2i& vecCursorPosition);
	bool									onMouseWheelUp(bxcf::Vec2i& vecCursorPosition);
	void									onRender(void);

	bool									doesControlUsePosition(bxcf::Vec2i& vecPoint);

	uint32									getActiveIndex(void);

	CTab*					addTab(std::string strTabText = "New Tab", bool bSetActiveTab = false, std::string strStyleGroups = "");
	template <class TabClass>
	TabClass*								addTab(std::string strTabText = "New Tab", bool bSetActiveTab = false, std::string strStyleGroups = "");
	void									removeTab(CTab *pTab);

	CTab*					getTabFromPosition(bxcf::Vec2i& vecPoint);
	bool									isPointOverTab(bxcf::Vec2i& vecPoint);

	void									bindTabLayer(CTab *pTab, CLayer *pLayer);
	void									unbindTabLayer(CTab *pTab);
	bool									isTabLayerBound(CTab *pTab);
	void									applyTabLayer(CTab *pTab, CTab *pPreviousTab);

	void									setActiveTab(CTab* pActiveTab) { m_pActiveTab = pActiveTab; }
	CTab*					getActiveTab(void) { return m_pActiveTab; }

	void									setMouseHoverTab(CTab *pTab) { m_pMouseHoverTab = pTab; }
	CTab*					getMouseHoverTab(void) { return m_pMouseHoverTab; }
	void									clearMouseHoverTab(void) { m_pMouseHoverTab = nullptr; }

	void									setActiveTabHeightDifference(uint32 uiActiveTabHeightDifference) { m_uiActiveTabHeightDifference = uiActiveTabHeightDifference; }
	uint32									getActiveTabHeightDifference(void) { return m_uiActiveTabHeightDifference; }

	void									setDefaultText(std::string strDefaultText) { m_strDefaultText = strDefaultText; }
	std::string								getDefaultText(void) { return m_strDefaultText; }

private:
	CTab*									m_pActiveTab;
	CTab*									m_pMouseHoverTab;
	uint32													m_uiActiveTabHeightDifference;
	std::string												m_strDefaultText;
	std::unordered_map<CTab*, CLayer*>	m_umapTabLayers;
};

template <class TabClass>
TabClass*									bxgx::CTabBar::addTab(std::string strTabText, bool bSetActiveTab, std::string strStyleGroups)
{
	TabClass *pTab = new TabClass;
	pTab->setTabControl(this);
	pTab->setText(strTabText);
	if (bSetActiveTab)
	{
		setActiveTab(pTab);
	}
	pTab->setStyleGroups(CString2::split(strStyleGroups, " "));
	addEntry(pTab);
	return pTab;
}