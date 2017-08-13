#ifndef CGUILayer_H
#define CGUILayer_H

#include "Type/Types.h"
#include "Pool/CVectorPool.h"
#include "Shape/CGUIShape.h"
#include "Control/CGUIControl.h"
#include "Control/eGUIControl.h"
#include "Type/Vector/Vec2i.h"
#include "Type/Vector/Vec2u.h"
#include "Event/eEvent.h"
#include "Event/CGUIEventUtilizer.h"
#include <string>
#include <vector>

class CCircleShape;
class CEllipseShape;
class CLineShape;
class CPolygonShape;
class CRectangleShape;
class CSquareShape;
class CTriangleShape;

class CButtonControl;
class CCheckControl;
class CDropControl;
class CTextBoxControl;
class CImageControl;
class CGridControl;
class CMenuControl;
class CProgressControl;
class CRadioControl;
class CScrollControl;
class CTabBarControl;
class CTextControl;

class CGUIStyles;
class CGUIItem;

class CGUILayer : public CGUIEventUtilizer, public CGUIStyleableEntity
{
public:
	CGUILayer(void);

	void					unload(void) {}

	void					bindEvents(void);
	void					unbindEvents(void);

	void					unserialize(void);
	void					serialize(void);

	uint32					getItemType(void) { return bxgx::item::LAYER; }
	uint32					getItemSubType(void) { return bxgx::item::layer::TYPE_1; }

	bool					isPointInItem(bxcf::Vec2i& vecPoint);
	bool					doesItemHaveFocus(void) { return true; }

	bool					onLeftMouseUp(bxcf::Vec2i& vecCursorPoint);

	void					setWindow(CWindow *pWindow) { m_pWindow = pWindow; }
	CWindow*				getWindow(void) { return m_pWindow; }

	void					setEnabled(bool bEnabled);
	void					setEnabledWithoutEvents(bool bEnabled) { m_bEnabled = bEnabled; }
	bool					isEnabled(void) { return m_bEnabled; }

	void					setId(uint32 uiId) { m_uiId = uiId; }
	uint32					getId(void) { return m_uiId; }

	CGUIItem*				getItemByPoint(bxcf::Vec2i& vecPoint, eGUIControl eControlType = GUI_CONTROL_UNKNOWN);

	// controls
	CGUIControl*			addControl(eGUIControl eControlId, std::string strStyleGroups = "", uint32 uiItemId = -1);

	CButtonControl*			addButton(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize, std::string strButtonText, std::string strStyleGroups = "", uint32 uiItemId = -1);
	CCheckControl*			addCheck(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize, std::string strCheckText, std::string strStyleGroups = "", uint32 uiItemId = -1);
	CDropControl*			addDrop(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize, std::string strDefaultText, std::string strStyleGroups = "", uint32 uiItemId = -1);
	CImageControl*			addImage(bxcf::Vec2i& vecPosition, std::string strImagePath, bxcf::Vec2u vecSize = bxcf::Vec2u(0, 0), std::string strStyleGroups = "", uint32 uiItemId = -1);
	// todo CImageControl*			addImageMem(bxcf::Vec2i& vecPosition, std::string& strImageData, bxcf::Vec2u vecSize = bxcf::Vec2u(0, 0), std::string strStyleGroups = "", uint32 uiItemId = -1);
	CGridControl*			addGrid(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize, std::string strStyleGroups = "", uint32 uiItemId = -1);
	CMenuControl*			addMenu(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize, std::string strStyleGroups = "", uint32 uiItemId = -1);
	CProgressControl*		addProgress(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize, std::string strStyleGroups = "", uint32 uiItemId = -1);
	CRadioControl*			addRadio(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize, std::string strRadioText, std::string strStyleGroups = "", uint32 uiItemId = -1);
	CScrollControl*			addScroll(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize, std::string strStyleGroups = "", uint32 uiItemId = -1);
	CTabBarControl*			addTabBar(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize, std::string strStyleGroups = "", uint32 uiItemId = -1);
	CTextControl*			addText(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize, std::string strText, std::string strStyleGroups = "", uint32 uiItemId = -1);
	CTextBoxControl*		addTextBox(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize, std::string strText = "", bool bMultiLine = false, std::string strStyleGroups = "", uint32 uiItemId = -1);

	CButtonControl*			addButton(int32 x, int32 y, int32 w, int32 h, std::string strButtonText, std::string strStyleGroups = "", uint32 uiItemId = -1);
	CCheckControl*			addCheck(int32 x, int32 y, int32 w, int32 h, std::string strCheckText, std::string strStyleGroups = "", uint32 uiItemId = -1);
	CDropControl*			addDrop(int32 x, int32 y, int32 w, int32 h, std::string strDefaultText, std::string strStyleGroups = "", uint32 uiItemId = -1);
	CImageControl*			addImage(int32 x, int32 y, std::string strImagePath, int32 w = 0, int32 h = 0, std::string strStyleGroups = "", uint32 uiItemId = -1);
	CGridControl*			addGrid(int32 x, int32 y, int32 w, int32 h, std::string strStyleGroups = "", uint32 uiItemId = -1);
	CMenuControl*			addMenu(int32 x, int32 y, int32 w, int32 h, std::string strStyleGroups = "", uint32 uiItemId = -1);
	CProgressControl*		addProgress(int32 x, int32 y, int32 w, int32 h, std::string strStyleGroups = "", uint32 uiItemId = -1);
	CRadioControl*			addRadio(int32 x, int32 y, int32 w, int32 h, std::string strRadioText, std::string strStyleGroups = "", uint32 uiItemId = -1);
	CScrollControl*			addScroll(int32 x, int32 y, int32 w, int32 h, std::string strStyleGroups = "", uint32 uiItemId = -1);
	CTabBarControl*			addTabBar(int32 x, int32 y, int32 w, int32 h, std::string strStyleGroups = "", uint32 uiItemId = -1);
	CTextControl*			addText(int32 x, int32 y, int32 w, int32 h, std::string strText, std::string strStyleGroups = "", uint32 uiItemId = -1);
	CTextBoxControl*		addTextBox(int32 x, int32 y, int32 w, int32 h, std::string strText = "", bool bMultiLine = false, std::string strStyleGroups = "", uint32 uiItemId = -1);

	//CTextControl*			addText(int32 x, int32 y, int32 w, int32 h, std::string strText, std::string strStyles);

	// shapes
	CGUIShape*				addShape(eGUIShape eShapeId, std::string strStyleGroups = "", uint32 uiItemId = -1);

	CLineShape*				addLine(bxcf::Vec2i& vecPoint1, bxcf::Vec2i& vecPoint2, std::string strStyleGroups = "", uint32 uiItemId = -1);
	CSquareShape*			addSquare(bxcf::Vec2i& vecPosition, uint32 uiSideLength, std::string strStyleGroups = "", uint32 uiItemId = -1);
	CRectangleShape*		addRectangle(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize, std::string strStyleGroups = "", uint32 uiItemId = -1);
	CCircleShape*			addCircle(bxcf::Vec2i& vecPosition, uint32 uiRadius, std::string strStyleGroups = "", uint32 uiItemId = -1);		// position is top left of circle
	CEllipseShape*			addEllipse(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize, std::string strStyleGroups = "", uint32 uiItemId = -1);
	CPolygonShape*			addPolygon(std::vector<bxcf::Vec2i>& vecPoints, std::string strStyleGroups = "", uint32 uiItemId = -1);

	CLineShape*				addLine(int32 x1, int32 y1, int32 x2, int32 y2, std::string strStyleGroups = "", uint32 uiItemId = -1);
	CSquareShape*			addSquare(int32 x, int32 y, int32 w, std::string strStyleGroups = "", uint32 uiItemId = -1);
	CRectangleShape*		addRectangle(int32 x, int32 y, int32 w, int32 h, std::string strStyleGroups = "", uint32 uiItemId = -1);
	CCircleShape*			addCircle(int32 x, int32 y, int32 r, std::string strStyleGroups = "", uint32 uiItemId = -1);		// position is top left of circle
	CEllipseShape*			addEllipse(int32 x, int32 y, int32 rw, int32 rh, std::string strStyleGroups = "", uint32 uiItemId = -1);
	
	CTriangleShape*			addTriangle(bxcf::Vec2i& vecPoint1, bxcf::Vec2i& vecPoint2, bxcf::Vec2i& vecPoint3, std::string strStyleGroups = "", uint32 uiItemId = -1);		// scalene or any triangle type
	CTriangleShape*			addEquilateralTriangle(bxcf::Vec2i& vecPosition, float32 fSideLength, uint32 uiPointingDirection, std::string strStyleGroups = "", uint32 uiItemId = -1); // [parameter uiPointingDirection] Left=1,Top=2,Right=3,Bottom=4,TopLeft=5,TopRight=6,BottomRight=7,BottomLeft=8
	CTriangleShape*			addEquilateralTriangle(bxcf::Vec2i& vecBottomLeftPoint, bxcf::Vec2i& vecBottomRightPoint, std::string strStyleGroups = "", uint32 uiItemId = -1);
	CTriangleShape*			addEquilateralTriangle(bxcf::Vec2i& vecBottomLeftPoint, float32 fSideLength, float32 fBaseAngle = 0.0f, std::string strStyleGroups = "", uint32 uiItemId = -1);	// base angle parameter is in degrees
	CTriangleShape*			addIsoscelesTriangle(bxcf::Vec2i& vecPosition, float32 fBaseLength, float32 fLegLength, uint32 uiPointingDirection, std::string strStyleGroups = "", uint32 uiItemId = -1); // [parameter uiPointingDirection] Left=1,Top=2,Right=3,Bottom=4,TopLeft=5,TopRight=6,BottomRight=7,BottomLeft=8
	CTriangleShape*			addIsoscelesTriangle(bxcf::Vec2i& vecBaseCenterPoint, bxcf::Vec2i& vecTipPoint, uint32 uiBaseHalfWidth, std::string strStyleGroups = "", uint32 uiItemId = -1);
	CTriangleShape*			addIsoscelesTriangle(bxcf::Vec2i& vecBottomLeftPoint, float32 fBaseLength, float32 fTipAngle = 25.0f, float32 fBaseAngle = 0.0f, std::string strStyleGroups = "", uint32 uiItemId = -1);	// tip angle parameter is in degrees

	// CGUILayer continued.
	bxcf::CVectorPool<CGUIShape*>*		getShapes(void) { return m_pShapes; }
	bxcf::CVectorPool<CGUIControl*>*	getControls(void) { return m_pControls; }

	CGUIControl*				getControlById(uint32 uiControlId);
	CGUIShape*					getShapeById(uint32 uiShapeId);

	void						setDropWithListOpen(CDropControl *pDrop) { m_pDropWithListOpen = pDrop; }
	CDropControl*				getDropWithListOpen(void) { return m_pDropWithListOpen; }
	void						clearDropWithListOpen(void) { m_pDropWithListOpen = nullptr; }

private:
	void						_addControl(CGUIControl *pWindowControl, bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize, std::string& strStyleGroups, uint32 uiItemId);
	void						_addControl(CGUIControl *pWindowControl, std::string& strStyleGroups, uint32 uiItemId);
	void						_addShape(CGUIShape *pShape, std::string& strStyleGroups, uint32 uiItemId);

	CGUIShape*					createShapeFromId(eGUIShape eShapeId);
	CGUIControl*				createControlFromId(eGUIControl eControlId);

protected:
	CWindow*							m_pWindow;

private:
	bool								m_bEnabled;
	CDropControl*						m_pDropWithListOpen;
	uint32								m_uiId;
	bxcf::CVectorPool<CGUIShape*>*		m_pShapes;
	bxcf::CVectorPool<CGUIControl*>*	m_pControls;
};

#endif