#pragma once

#include "nsbxgx.h"
#include "Type/Types.h"
#include "Control/Base/Control.h"
#include "Control/Entries/Tab.h"
#include "Event/Events.h"
#include <string>
#include <unordered_map>

class bxgx::Layer;

class bxgx::TabBar : public bxgx::Control, public bxcf::VectorPool<Tab*>
{
public:
	TabBar(void);

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

	Tab*					addTab(std::string strTabText = "New Tab", bool bSetActiveTab = false, std::string strStyleGroups = "");
	template <class TabClass>
	TabClass*								addTab(std::string strTabText = "New Tab", bool bSetActiveTab = false, std::string strStyleGroups = "");
	void									removeTab(Tab *pTab);

	Tab*					getTabFromPosition(bxcf::Vec2i& vecPoint);
	bool									isPointOverTab(bxcf::Vec2i& vecPoint);

	void									bindTabLayer(Tab *pTab, Layer *pLayer);
	void									unbindTabLayer(Tab *pTab);
	bool									isTabLayerBound(Tab *pTab);
	void									applyTabLayer(Tab *pTab, Tab *pPreviousTab);

	void									setActiveTab(Tab* pActiveTab) { m_pActiveTab = pActiveTab; }
	Tab*					getActiveTab(void) { return m_pActiveTab; }

	void									setMouseHoverTab(Tab *pTab) { m_pMouseHoverTab = pTab; }
	Tab*					getMouseHoverTab(void) { return m_pMouseHoverTab; }
	void									clearMouseHoverTab(void) { m_pMouseHoverTab = nullptr; }

	void									setActiveTabHeightDifference(uint32 uiActiveTabHeightDifference) { m_uiActiveTabHeightDifference = uiActiveTabHeightDifference; }
	uint32									getActiveTabHeightDifference(void) { return m_uiActiveTabHeightDifference; }

	void									setDefaultText(std::string strDefaultText) { m_strDefaultText = strDefaultText; }
	std::string								getDefaultText(void) { return m_strDefaultText; }

private:
	Tab*									m_pActiveTab;
	Tab*									m_pMouseHoverTab;
	uint32													m_uiActiveTabHeightDifference;
	std::string												m_strDefaultText;
	std::unordered_map<Tab*, Layer*>	m_umapTabLayers;
};

template <class TabClass>
TabClass*									bxgx::TabBar::addTab(std::string strTabText, bool bSetActiveTab, std::string strStyleGroups)
{
	TabClass *pTab = new TabClass;
	pTab->setTabControl(this);
	pTab->setText(strTabText);
	if (bSetActiveTab)
	{
		setActiveTab(pTab);
	}
	pTab->setStyleGroups(String::split(strStyleGroups, " "));
	addEntry(pTab);
	return pTab;
}