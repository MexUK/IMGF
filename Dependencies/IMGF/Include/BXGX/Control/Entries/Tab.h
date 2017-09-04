#pragma once

#include "bxgx.h"
#include "Type/Types.h"
#include "Control/Components/TextComponent.h"
#include "Item/Layer/LayerItem.h"
#include "Item/Render/ERenderItem.h"
#include <string>
#include <vector>

class bxgx::TabBar;

class bxgx::Tab : public bxgx::TextComponent, public LayerItem
{
public:
	Tab(void);
	
	void									unload(void) {}

	void									setTabBar(TabBar *pTabControl);
	TabBar*							getTabBar(void) { return m_pTabBar; }

	bxgx::item::ERenderItem						getItemType(void) { return bxgx::item::CONTROL; } // todo - CONTROL_COMPONENT
	uint32									getItemSubType(void) { return 0; } // todo - CONTROL_COMPONENT_TAB
	bool									isPointInItem(bxcf::Vec2i& vecPoint) { return false; } // todo
	bool									doesItemHaveFocus(void) { return false; } // todo

	void									unserialize(bool bSkipItemId = false) {} // todo
	void									serialize(void) {} // todo

	bxcf::Vec2i								getBoundingRectanglePosition(void) { return bxcf::Vec2i(0, 0); } // todo
	bxcf::Vec2u								getBoundingRectangleSize(void) { return bxcf::Vec2u(0, 0); } // todo
	void									moveItem(bxcf::Vec2i& vecItemPositionChange) {} // todo
	void									resizeItemViaOffsets(bxcf::Vec2i& vecItemSizeChange) {} // todo

	void									setActiveTab(void);
	bool									isActiveTab(void);

	void									setStyleGroups(std::vector<std::string>& vecStyleGroups);
	void									setStyleGroups(std::vector<uint32>& vecStyleGroups) { m_vecStyleGroups = vecStyleGroups; }
	std::vector<uint32>&					getStyleGroups(void) { return m_vecStyleGroups; }

	uint32									getIndex(void);

private:
	TabBar*							m_pTabBar;
	std::vector<uint32>						m_vecStyleGroups;
};