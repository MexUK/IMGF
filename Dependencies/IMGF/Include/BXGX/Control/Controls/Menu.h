#pragma once

#include "nsbxgx.h"
#include "Type/Types.h"
#include "Pool/VectorPool.h"
#include "Control/Base/Control.h"
#include "Type/Axis/E2DAxis.h"
#include <mutex>

class bxgx::MenuItem;

extern std::mutex mutexControlInput;

class bxgx::Menu : public bxgx::Control, public bxcf::VectorPool<bxgx::MenuItem*>
{
public:
	Menu(void);

	void									bindEvents(void);
	void									bindEventsWithoutRender(void);

	void									unserialize(bool bSkipControlId = false);
	void									serialize(void);

	bool									doesControlUsePosition(bxcf::Vec2i& vecPoint);

	bool									onLeftMouseDown(bxcf::Vec2i& vecCursorPoint);
	bool									onMouseEnter(bxcf::Vec2i& vecCursorPoint);
	bool									onMouseExit(bxcf::Vec2i& vecCursorPoint);
	bool									onMouseMove(bxcf::Vec2i& vecCursorPoint);
	void									onRenderAfter(void);

	void									setContainerMenuItem(MenuItem* pContainerMenuItem) { m_pContainerMenuItem = pContainerMenuItem; }
	MenuItem*								getContainerMenuItem(void) { return m_pContainerMenuItem; }

	void									setOrientation(bxcf::E2DAxis eOrientation) { m_uiOrientation = eOrientation; }
	bxcf::E2DAxis							getOrientation(void) { return m_uiOrientation; }

	void									setActiveMenuItem(MenuItem* pActiveMenuItem);
	MenuItem*								getActiveMenuItem(void) { return m_pActiveMenuItem; }

	void									setHoverMenuItem(MenuItem* pHoverMenuItem);
	MenuItem*								getHoverMenuItem(void) { return m_pHoverMenuItem; }

	void									setMenuItemLength(uint32 uiMenuItemLength) { m_uiMenuItemLength = uiMenuItemLength; }
	uint32									getMenuItemLength(void) { return m_uiMenuItemLength; }

	Menu*									getMenuByPoint(bxcf::Vec2i& vecPoint);

	void									unexpandAllMenus(void);

	MenuItem*								addMenuItem(std::string strText, uint32 uiItemId = -1);
	std::vector<MenuItem*>					addMenuItems(uint32 uiItemCount, ...);
	void									removeMenuItem(MenuItem *pMenuItem);

	void									checkToResizeMenuWidth(void);
	void									repositionAllExpandableMenus(uint32 uiMenuWidth);
	void									repositionMenu(uint32 uiMenuWidth);
	void									resizeMenuWidth(uint32 uiMenuWidth);

private:
	void									drawMenu(void);

private:
	MenuItem*								m_pContainerMenuItem;
	bxcf::E2DAxis							m_uiOrientation;
	MenuItem*								m_pActiveMenuItem;
	MenuItem*								m_pHoverMenuItem;
	uint32									m_uiMenuItemLength;
};