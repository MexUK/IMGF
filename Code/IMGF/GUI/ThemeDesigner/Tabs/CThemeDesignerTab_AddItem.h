#ifndef CThemeDesignerTab_AddItem_H
#define CThemeDesignerTab_AddItem_H

#include "Type/Vector/Vec2i.h"
#include "Type/Vector/Vec2u.h"
#include "Shape/eGUIShape.h"
#include "Control/eGUIControl.h"
#include "GUI/ThemeDesigner/Tab/CThemeDesignerTab.h"

class CThemeDesignerTab_AddItem : public CThemeDesignerTab
{
public:
	CThemeDesignerTab_AddItem(CThemeDesigner *pThemeDesigner);

	void													bindEvents(void);
	void													initDesign(void);

	void													onLeftMouseDown(bxcf::Vec2i& vecCursorPosition);
	void													onMouseMove(bxcf::Vec2i& vecCursorPosition);
	void													onLeftMouseDown_MainWindow(bxcf::Vec2i& vecCursorPosition);
	void													onLeftMouseDown_MainWindow_WindowEventType(bxcf::Vec2i& vecCursorPosition);

	uint32													getTabShapeIndexFromPoint(bxcf::Vec2i& vecCursorPosition);
	uint32													getTabControlIndexFromPoint(bxcf::Vec2i& vecCursorPosition);
	bxcf::Vec2i												getShapeRowPoint(uint32 uiShapeRowIndex);
	bxcf::Vec2i												getControlRowPoint(uint32 uiControlRowIndex);
	eGUIShape												getShapeIdFromIndex(uint32 uiShapeIndex);
	eGUIControl												getControlIdFromIndex(uint32 uiControlIndex);

	bxcf::Vec2u													getControlDefaultSize(eGUIControl eControlId);

	void													setHoveredItemType(uint32 uiHoveredItemType) { m_uiHoveredItemType = uiHoveredItemType; }
	uint32													getHoveredItemType(void) { return m_uiHoveredItemType; }

	void													setActiveItemType(uint32 uiActiveItemType) { m_uiActiveItemType = uiActiveItemType; }
	uint32													getActiveItemType(void) { return m_uiActiveItemType; }

	void													setHoveredShapeId(eGUIShape eHoveredShapeId) { m_eHoveredShapeId = eHoveredShapeId; }
	eGUIShape												getHoveredShapeId(void) { return m_eHoveredShapeId; }

	void													setHoveredControlId(eGUIControl eHoveredControlId) { m_eHoveredControlId = eHoveredControlId; }
	eGUIControl												getHoveredControlId(void) { return m_eHoveredControlId; }

	void													setActiveShapeId(eGUIShape eActiveShapeId) { m_eActiveShapeId = eActiveShapeId; }
	eGUIShape												getActiveShapeId(void) { return m_eActiveShapeId; }

	void													setActiveControlId(eGUIControl eActiveControlId) { m_eActiveControlId = eActiveControlId; }
	eGUIControl												getActiveControlId(void) { return m_eActiveControlId; }

	void													setShapeIconStartPosition(bxcf::Vec2i& vecShapeIconStartPosition) { m_vecShapeIconStartPosition = vecShapeIconStartPosition; }
	bxcf::Vec2i&											getShapeIconStartPosition(void) { return m_vecShapeIconStartPosition; }

	void													setShapeTextStartPosition(bxcf::Vec2i& vecShapeTextStartPosition) { m_vecShapeTextStartPosition = vecShapeTextStartPosition; }
	bxcf::Vec2i&											getShapeTextStartPosition(void) { return m_vecShapeTextStartPosition; }

	void													setControlIconStartPosition(bxcf::Vec2i& vecControlIconStartPosition) { m_vecControlIconStartPosition = vecControlIconStartPosition; }
	bxcf::Vec2i&											getControlIconStartPosition(void) { return m_vecControlIconStartPosition; }

	void													setControlTextStartPosition(bxcf::Vec2i& vecControlTextStartPosition) { m_vecControlTextStartPosition = vecControlTextStartPosition; }
	bxcf::Vec2i&											getControlTextStartPosition(void) { return m_vecControlTextStartPosition; }

	void													setItemRowSize(bxcf::Vec2u& vecItemRowSize) { m_vecItemRowSize = vecItemRowSize; }
	bxcf::Vec2u&												getItemRowSize(void) { return m_vecItemRowSize; }

	void													setItemSize(bxcf::Vec2u& vecItemSize) { m_vecItemSize = vecItemSize; }
	bxcf::Vec2u&												getItemSize(void) { return m_vecItemSize; }

private:
	uint32													m_uiHoveredItemType;
	uint32													m_uiActiveItemType;
	eGUIShape												m_eHoveredShapeId;
	eGUIControl												m_eHoveredControlId;
	eGUIShape												m_eActiveShapeId;
	eGUIControl												m_eActiveControlId;
	bxcf::Vec2i												m_vecShapeIconStartPosition;
	bxcf::Vec2i												m_vecShapeTextStartPosition;
	bxcf::Vec2i												m_vecControlIconStartPosition;
	bxcf::Vec2i												m_vecControlTextStartPosition;
	uint32													m_uiItemRowHeight;
	bxcf::Vec2u													m_vecItemRowSize;
	bxcf::Vec2u													m_vecItemSize;
};

#endif