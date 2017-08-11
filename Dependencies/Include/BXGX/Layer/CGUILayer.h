#ifndef CGUILayer_H
#define CGUILayer_H

#include "Type/Types.h"
#include "Pool/CVectorPool.h"
#include "Shape/CGUIShape.h"
#include "Control/CGUIControl.h"
#include "Control/eGUIControl.h"
#include "Type/Vector/CPoint2D.h"
#include "Type/Vector/CSize2D.h"
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

	void					triggerEvent(bxcf::eEvent eEventId, void *pTriggerArgument);

	void					unserialize(void);
	void					serialize(void);

	uint32					getItemType(void) { return bxgx::item::LAYER; }
	uint32					getItemSubType(void) { return bxgx::item::layer::TYPE_1; }

	bool					isPointInItem(bxcf::CPoint2D& vecPoint);
	bool					doesItemHaveFocus(void) { return true; }

	bool					onLeftMouseUp(bxcf::CPoint2D& vecCursorPoint);
	bool					onMouseMove(bxcf::CPoint2D& vecCursorPoint);

	void					setWindow(CWindow *pWindow) { m_pWindow = pWindow; }
	CWindow*				getWindow(void) { return m_pWindow; }

	void					setEnabled(bool bEnabled);
	void					setEnabledWithoutEvents(bool bEnabled) { m_bEnabled = bEnabled; }
	bool					isEnabled(void) { return m_bEnabled; }

	void					setId(uint32 uiId) { m_uiId = uiId; }
	uint32					getId(void) { return m_uiId; }

	CGUIItem*				getItemByPoint(bxcf::CPoint2D& vecPoint, eGUIControl eControlType = GUI_CONTROL_UNKNOWN);

	// controls
	CGUIControl*			addControl(eGUIControl eControlId, std::string strStyleGroups = "", uint32 uiItemId = -1);

	CButtonControl*			addButton(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize, std::string strButtonText, std::string strStyleGroups = "", uint32 uiItemId = -1);
	CCheckControl*			addCheck(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize, std::string strCheckText, std::string strStyleGroups = "", uint32 uiItemId = -1);
	CDropControl*			addDrop(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize, std::string strDefaultText, std::string strStyleGroups = "", uint32 uiItemId = -1);
	CImageControl*			addImage(bxcf::CPoint2D& vecPosition, std::string& strImagePath, bxcf::CSize2D vecSize = bxcf::CSize2D(0, 0), std::string strStyleGroups = "", uint32 uiItemId = -1);
	// todo CImageControl*			addImageMem(bxcf::CPoint2D& vecPosition, std::string& strImageData, bxcf::CSize2D vecSize = bxcf::CSize2D(0, 0), std::string strStyleGroups = "", uint32 uiItemId = -1);
	CGridControl*			addGrid(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize, std::string strStyleGroups = "", uint32 uiItemId = -1);
	CMenuControl*			addMenu(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize, std::string strStyleGroups = "", uint32 uiItemId = -1);
	CProgressControl*		addProgress(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize, std::string strStyleGroups = "", uint32 uiItemId = -1);
	CRadioControl*			addRadio(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize, std::string strRadioText, std::string strStyleGroups = "", uint32 uiItemId = -1);
	CScrollControl*			addScroll(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize, std::string strStyleGroups = "", uint32 uiItemId = -1);
	CTabBarControl*			addTabBar(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize, std::string strStyleGroups = "", uint32 uiItemId = -1);
	CTextControl*			addText(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize, std::string strText, std::string strStyleGroups = "", uint32 uiItemId = -1);
	CTextBoxControl*		addTextBox(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize, std::string strText = "", bool bMultiLine = false, std::string strStyleGroups = "", uint32 uiItemId = -1);

	CButtonControl*			addButton(int32 x, int32 y, int32 w, int32 h, std::string strButtonText, std::string strStyleGroups = "", uint32 uiItemId = -1);
	CCheckControl*			addCheck(int32 x, int32 y, int32 w, int32 h, std::string strCheckText, std::string strStyleGroups = "", uint32 uiItemId = -1);
	CDropControl*			addDrop(int32 x, int32 y, int32 w, int32 h, std::string strDefaultText, std::string strStyleGroups = "", uint32 uiItemId = -1);
	CImageControl*			addImage(int32 x, int32 y, std::string& strImagePath, int32 w = 0, int32 h = 0, std::string strStyleGroups = "", uint32 uiItemId = -1);
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

	CLineShape*				addLine(bxcf::CPoint2D& vecPoint1, bxcf::CPoint2D& vecPoint2, std::string strStyleGroups = "", uint32 uiItemId = -1);
	CSquareShape*			addSquare(bxcf::CPoint2D& vecPosition, uint32 uiSideLength, std::string strStyleGroups = "", uint32 uiItemId = -1);
	CRectangleShape*		addRectangle(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize, std::string strStyleGroups = "", uint32 uiItemId = -1);
	CCircleShape*			addCircle(bxcf::CPoint2D& vecPosition, uint32 uiRadius, std::string strStyleGroups = "", uint32 uiItemId = -1);		// position is top left of circle
	CEllipseShape*			addEllipse(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize, std::string strStyleGroups = "", uint32 uiItemId = -1);
	CPolygonShape*			addPolygon(std::vector<bxcf::CPoint2D>& vecPoints, std::string strStyleGroups = "", uint32 uiItemId = -1);

	CLineShape*				addLine(int32 x1, int32 y1, int32 x2, int32 y2, std::string strStyleGroups = "", uint32 uiItemId = -1);
	CSquareShape*			addSquare(int32 x, int32 y, int32 w, std::string strStyleGroups = "", uint32 uiItemId = -1);
	CRectangleShape*		addRectangle(int32 x, int32 y, int32 w, int32 h, std::string strStyleGroups = "", uint32 uiItemId = -1);
	CCircleShape*			addCircle(int32 x, int32 y, int32 r, std::string strStyleGroups = "", uint32 uiItemId = -1);		// position is top left of circle
	CEllipseShape*			addEllipse(int32 x, int32 y, int32 rw, int32 rh, std::string strStyleGroups = "", uint32 uiItemId = -1);
	
	CTriangleShape*			addTriangle(bxcf::CPoint2D& vecPoint1, bxcf::CPoint2D& vecPoint2, bxcf::CPoint2D& vecPoint3, std::string strStyleGroups = "", uint32 uiItemId = -1);		// scalene or any triangle type
	CTriangleShape*			addEquilateralTriangle(bxcf::CPoint2D& vecPosition, float32 fSideLength, uint32 uiPointingDirection, std::string strStyleGroups = "", uint32 uiItemId = -1); // [parameter uiPointingDirection] Left=1,Top=2,Right=3,Bottom=4,TopLeft=5,TopRight=6,BottomRight=7,BottomLeft=8
	CTriangleShape*			addEquilateralTriangle(bxcf::CPoint2D& vecBottomLeftPoint, bxcf::CPoint2D& vecBottomRightPoint, std::string strStyleGroups = "", uint32 uiItemId = -1);
	CTriangleShape*			addEquilateralTriangle(bxcf::CPoint2D& vecBottomLeftPoint, float32 fSideLength, float32 fBaseAngle = 0.0f, std::string strStyleGroups = "", uint32 uiItemId = -1);	// base angle parameter is in degrees
	CTriangleShape*			addIsoscelesTriangle(bxcf::CPoint2D& vecPosition, float32 fBaseLength, float32 fLegLength, uint32 uiPointingDirection, std::string strStyleGroups = "", uint32 uiItemId = -1); // [parameter uiPointingDirection] Left=1,Top=2,Right=3,Bottom=4,TopLeft=5,TopRight=6,BottomRight=7,BottomLeft=8
	CTriangleShape*			addIsoscelesTriangle(bxcf::CPoint2D& vecBaseCenterPoint, bxcf::CPoint2D& vecTipPoint, uint32 uiBaseHalfWidth, std::string strStyleGroups = "", uint32 uiItemId = -1);
	CTriangleShape*			addIsoscelesTriangle(bxcf::CPoint2D& vecBottomLeftPoint, float32 fBaseLength, float32 fTipAngle = 25.0f, float32 fBaseAngle = 0.0f, std::string strStyleGroups = "", uint32 uiItemId = -1);	// tip angle parameter is in degrees

	// CGUILayer continued.
	bxcf::CVectorPool<CGUIShape*>*		getShapes(void) { return m_pShapes; }
	bxcf::CVectorPool<CGUIControl*>*	getControls(void) { return m_pControls; }

	CGUIControl*				getControlById(uint32 uiControlId);
	CGUIShape*					getShapeById(uint32 uiShapeId);

	void						setItemCursorHover(CGUIItem *pItem) { m_pItemCursorHover = pItem; }
	CGUIItem*					getItemCursorHover(void) { return m_pItemCursorHover; }
	void						clearItemCursorHover(void) { m_pItemCursorHover = nullptr; }

	void						setDropWithListOpen(CDropControl *pDrop) { m_pDropWithListOpen = pDrop; }
	CDropControl*				getDropWithListOpen(void) { return m_pDropWithListOpen; }
	void						clearDropWithListOpen(void) { m_pDropWithListOpen = nullptr; }

private:
	void						_addControl(CGUIControl *pWindowControl, bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize, std::string& strStyleGroups, uint32 uiItemId);
	void						_addControl(CGUIControl *pWindowControl, std::string& strStyleGroups, uint32 uiItemId);
	void						_addShape(CGUIShape *pShape, std::string& strStyleGroups, uint32 uiItemId);

	CGUIShape*					createShapeFromId(eGUIShape eShapeId);
	CGUIControl*				createControlFromId(eGUIControl eControlId);

protected:
	CWindow*							m_pWindow;

private:
	bool								m_bEnabled;
	CGUIItem*							m_pItemCursorHover;
	CDropControl*						m_pDropWithListOpen;
	uint32								m_uiId;
	bxcf::CVectorPool<CGUIShape*>*		m_pShapes;
	bxcf::CVectorPool<CGUIControl*>*	m_pControls;
};

#endif