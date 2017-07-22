#ifndef CThemeDesignerTab_AddItem_H
#define CThemeDesignerTab_AddItem_H

#include "Type/Vector/CPoint2D.h"
#include "Type/Vector/CSize2D.h"
#include "Shape/eGUIShape.h"
#include "Control/eGUIControl.h"
#include "GUI/ThemeDesigner/Tab/CThemeDesignerTab.h"

class CThemeDesignerTab_AddItem : public CThemeDesignerTab
{
public:
	CThemeDesignerTab_AddItem(CThemeDesigner *pThemeDesigner);

	void													bindEvents(void);
	void													initDesign(void);

	void													onLeftMouseDown(bxa::CPoint2D& vecCursorPosition);
	void													onMouseMove(bxa::CPoint2D& vecCursorPosition);
	void													onLeftMouseDown_MainWindow(bxa::CPoint2D& vecCursorPosition);
	void													onLeftMouseDown_MainWindow_WindowEventType(bxa::CPoint2D& vecCursorPosition);

	uint32													getTabShapeIndexFromPoint(bxa::CPoint2D& vecCursorPosition);
	uint32													getTabControlIndexFromPoint(bxa::CPoint2D& vecCursorPosition);
	bxa::CPoint2D												getShapeRowPoint(uint32 uiShapeRowIndex);
	bxa::CPoint2D												getControlRowPoint(uint32 uiControlRowIndex);
	eGUIShape												getShapeIdFromIndex(uint32 uiShapeIndex);
	eGUIControl												getControlIdFromIndex(uint32 uiControlIndex);

	bxa::CSize2D													getControlDefaultSize(eGUIControl eControlId);

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

	void													setShapeIconStartPosition(bxa::CPoint2D& vecShapeIconStartPosition) { m_vecShapeIconStartPosition = vecShapeIconStartPosition; }
	bxa::CPoint2D&											getShapeIconStartPosition(void) { return m_vecShapeIconStartPosition; }

	void													setShapeTextStartPosition(bxa::CPoint2D& vecShapeTextStartPosition) { m_vecShapeTextStartPosition = vecShapeTextStartPosition; }
	bxa::CPoint2D&											getShapeTextStartPosition(void) { return m_vecShapeTextStartPosition; }

	void													setControlIconStartPosition(bxa::CPoint2D& vecControlIconStartPosition) { m_vecControlIconStartPosition = vecControlIconStartPosition; }
	bxa::CPoint2D&											getControlIconStartPosition(void) { return m_vecControlIconStartPosition; }

	void													setControlTextStartPosition(bxa::CPoint2D& vecControlTextStartPosition) { m_vecControlTextStartPosition = vecControlTextStartPosition; }
	bxa::CPoint2D&											getControlTextStartPosition(void) { return m_vecControlTextStartPosition; }

	void													setItemRowSize(bxa::CSize2D& vecItemRowSize) { m_vecItemRowSize = vecItemRowSize; }
	bxa::CSize2D&												getItemRowSize(void) { return m_vecItemRowSize; }

	void													setItemSize(bxa::CSize2D& vecItemSize) { m_vecItemSize = vecItemSize; }
	bxa::CSize2D&												getItemSize(void) { return m_vecItemSize; }

private:
	uint32													m_uiHoveredItemType;
	uint32													m_uiActiveItemType;
	eGUIShape												m_eHoveredShapeId;
	eGUIControl												m_eHoveredControlId;
	eGUIShape												m_eActiveShapeId;
	eGUIControl												m_eActiveControlId;
	bxa::CPoint2D												m_vecShapeIconStartPosition;
	bxa::CPoint2D												m_vecShapeTextStartPosition;
	bxa::CPoint2D												m_vecControlIconStartPosition;
	bxa::CPoint2D												m_vecControlTextStartPosition;
	uint32													m_uiItemRowHeight;
	bxa::CSize2D													m_vecItemRowSize;
	bxa::CSize2D													m_vecItemSize;
};

#endif