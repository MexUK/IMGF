#pragma once

#include "nsbxgx.h"
#include "Type/Types.h"
#include "Control/Components/TextComponent.h"
#include "Item/Render/RenderItem.h"

class bxgx::Menu;

class bxgx::MenuItem : public bxgx::TextComponent, public RenderItem
{
public:
	MenuItem(void);
	
	void									unload(void) {}

	item::ERenderItem						getItemType(void) { return item::CONTROL_ITEM; }
	uint32									getItemSubType(void) { return 0; }
	bool									isPointInItem(bxcf::Vec2i& vecPoint);
	bool									doesItemHaveFocus(void) { return false; }

	void									setContainerMenu(Menu *pContainerMenu);
	Menu*									getContainerMenu(void) { return m_pContainerMenu; }

	void									setExpandableMenu(Menu *pExpandableMenu) { m_pExpandableMenu = pExpandableMenu; }
	Menu*									getExpandableMenu(void) { return m_pExpandableMenu; }

	void									setActiveItem(bool bActiveItem) { m_bActiveItem = bActiveItem; }
	bool									isActiveItem(void) { return m_bActiveItem; }

	void									setHoverItem(bool bHoverItem) { m_bHoverItem = bHoverItem; }
	bool									isHoverItem(void) { return m_bHoverItem; }

	void									setMenuExpanded(bool bMenuExpanded) { m_bMenuExpanded = bMenuExpanded; }
	bool									isMenuExpanded(void) { return m_bMenuExpanded; }

	void									setId(uint32 uiId) { m_uiId = uiId; }
	uint32									getId(void) { return m_uiId; }

	void									setSize(bxcf::Vec2u& vecSize) { m_vecSize = vecSize; }
	bxcf::Vec2u&							getSize(void) { return m_vecSize; }

	bxcf::Vec2i								getPosition(void);

	Menu*									addMenu(void);
	bool									doesHaveMenu(void) { return m_pExpandableMenu != nullptr; }

private:
	Menu*									m_pContainerMenu;
	Menu*									m_pExpandableMenu;
	bool									m_bActiveItem;
	bool									m_bHoverItem;
	bool									m_bMenuExpanded;
	uint32									m_uiId;
	bxcf::Vec2u								m_vecSize;
};