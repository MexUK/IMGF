#ifndef CTabBarControlEntry_H
#define CTabBarControlEntry_H

#include "Type/Types.h"
#include "Controls/Components/CGUIControlComponent_Text.h"
#include "Styles/CGUIStyleableEntity.h"
#include "Event/CGUIEventUtilizer.h"
#include "Item/CGUIItem.h"
#include <string>
#include <vector>

class CTabBarControl;

class CTabBarControlEntry : public CGUIControlComponent_Text, public CGUIStyleableEntity, public CGUIItem
{
public:
	CTabBarControlEntry(void);
	
	void									unload(void) {}

	uint32									getItemType(void) { return bxgx::item::CONTROL; } // todo - CONTROL_COMPONENT
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

	void									setTabControl(CTabBarControl *pTabControl) { m_pTabControl = pTabControl; }
	CTabBarControl*							getTabControl(void) { return m_pTabControl; }

	void									setStyleGroups(std::vector<std::string>& vecStyleGroups);
	void									setStyleGroups(std::vector<uint32>& vecStyleGroups) { m_vecStyleGroups = vecStyleGroups; }
	std::vector<uint32>&					getStyleGroups(void) { return m_vecStyleGroups; }

	uint32									getIndex(void);

private:
	CTabBarControl*							m_pTabControl;
	std::vector<uint32>						m_vecStyleGroups;
};

#endif