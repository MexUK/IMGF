#ifndef CGUILayer_H
#define CGUILayer_H

#include "Type/Types.h"
#include "Pool/CVectorPool.h"
#include "Shape/CGUIShape.h"
#include "Control/CGUIControl.h"
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
class CEditControl;
class CImageControl;
class CListControl;
class CMenuControl;
class CProgressControl;
class CRadioControl;
class CScrollControl;
class CTabControl;
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

	bool					onMouseMove(bxcf::CPoint2D& vecCursorPoint);

	void					setWindow(CWindow *pWindow) { m_pWindow = pWindow; }
	CWindow*				getWindow(void) { return m_pWindow; }

	void					setEnabled(bool bEnabled);
	bool					isEnabled(void) { return m_bEnabled; }

	CGUIItem*				getItemByPoint(bxcf::CPoint2D& vecPoint);

	// controls
	CGUIControl*			addControl(eGUIControl eControlId, std::string strStyleGroup = "");

	CButtonControl*			addButton(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize, std::string strButtonText, std::string strStyleGroup = "");
	CCheckControl*			addCheck(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize, std::string strCheckText, std::string strStyleGroup = "");
	CDropControl*			addDrop(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize, std::string strStyleGroup = "");
	CEditControl*			addEdit(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize, std::string strEditText = "", bool bMultiLine = false, std::string strStyleGroup = "");
	CImageControl*			addImage(bxcf::CPoint2D& vecPosition, std::string& strImagePath, bxcf::CSize2D vecSize = bxcf::CSize2D(0, 0), std::string strStyleGroup = "");
	// todo CImageControl*			addImageMem(bxcf::CPoint2D& vecPosition, std::string& strImageData, bxcf::CSize2D vecSize = bxcf::CSize2D(0, 0), std::string strStyleGroup = "");
	CListControl*			addList(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize, std::string strStyleGroup = "");
	CMenuControl*			addMenu(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize, std::string strStyleGroup = "");
	CProgressControl*		addProgress(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize, std::string strStyleGroup = "");
	CRadioControl*			addRadio(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize, std::string strRadioText, std::string strStyleGroup = "");
	CScrollControl*			addScroll(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize, std::string strStyleGroup = "");
	CTabControl*			addTabBar(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize, std::string strStyleGroup = "");
	CTextControl*			addText(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize, std::string strText, std::string strStyleGroup = "");

	CButtonControl*			addButton(int32 x, int32 y, int32 w, int32 h, std::string strButtonText, std::string strStyleGroup = "");
	CCheckControl*			addCheck(int32 x, int32 y, int32 w, int32 h, std::string strCheckText, std::string strStyleGroup = "");
	CDropControl*			addDrop(int32 x, int32 y, int32 w, int32 h, std::string strStyleGroup = "");
	CEditControl*			addEdit(int32 x, int32 y, int32 w, int32 h, std::string strEditText = "", bool bMultiLine = false, std::string strStyleGroup = "");
	CImageControl*			addImage(int32 x, int32 y, std::string& strImagePath, int32 w = 0, int32 h = 0, std::string strStyleGroup = "");
	CListControl*			addList(int32 x, int32 y, int32 w, int32 h, std::string strStyleGroup = "");
	CMenuControl*			addMenu(int32 x, int32 y, int32 w, int32 h, std::string strStyleGroup = "");
	CProgressControl*		addProgress(int32 x, int32 y, int32 w, int32 h, std::string strStyleGroup = "");
	CRadioControl*			addRadio(int32 x, int32 y, int32 w, int32 h, std::string strRadioText, std::string strStyleGroup = "");
	CScrollControl*			addScroll(int32 x, int32 y, int32 w, int32 h, std::string strStyleGroup = "");
	CTabControl*			addTabBar(int32 x, int32 y, int32 w, int32 h, std::string strStyleGroup = "");
	CTextControl*			addText(int32 x, int32 y, int32 w, int32 h, std::string strText, std::string strStyleGroup = "");

	//CTextControl*			addText(int32 x, int32 y, int32 w, int32 h, std::string strText, std::string strStyles);

	// shapes
	CGUIShape*				addShape(eGUIShape eShapeId, std::string strStyleGroup = "");

	CLineShape*				addLine(bxcf::CPoint2D& vecPoint1, bxcf::CPoint2D& vecPoint2, std::string strStyleGroup = "");
	CSquareShape*			addSquare(bxcf::CPoint2D& vecPosition, uint32 uiSideLength, std::string strStyleGroup = "");
	CRectangleShape*		addRectangle(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize, std::string strStyleGroup = "");
	CCircleShape*			addCircle(bxcf::CPoint2D& vecPosition, uint32 uiRadius, std::string strStyleGroup = "");		// position is top left of circle
	CEllipseShape*			addEllipse(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize, std::string strStyleGroup = "");
	CPolygonShape*			addPolygon(std::vector<bxcf::CPoint2D>& vecPoints, std::string strStyleGroup = "");

	CLineShape*				addLine(int32 x1, int32 y1, int32 x2, int32 y2, std::string strStyleGroup = "");
	CSquareShape*			addSquare(int32 x, int32 y, int32 w, std::string strStyleGroup = "");
	CRectangleShape*		addRectangle(int32 x, int32 y, int32 w, int32 h, std::string strStyleGroup = "");
	CCircleShape*			addCircle(int32 x, int32 y, int32 r, std::string strStyleGroup = "");		// position is top left of circle
	CEllipseShape*			addEllipse(int32 x, int32 y, int32 rw, int32 rh, std::string strStyleGroup = "");
	
	CTriangleShape*			addTriangle(bxcf::CPoint2D& vecPoint1, bxcf::CPoint2D& vecPoint2, bxcf::CPoint2D& vecPoint3, std::string strStyleGroup = "");		// scalene or any triangle type
	CTriangleShape*			addEquilateralTriangle(bxcf::CPoint2D& vecPosition, float32 fSideLength, uint32 uiPointingDirection, std::string strStyleGroup = ""); // [parameter uiPointingDirection] Left=1,Top=2,Right=3,Bottom=4,TopLeft=5,TopRight=6,BottomRight=7,BottomLeft=8
	CTriangleShape*			addEquilateralTriangle(bxcf::CPoint2D& vecBottomLeftPoint, bxcf::CPoint2D& vecBottomRightPoint, std::string strStyleGroup = "");
	CTriangleShape*			addEquilateralTriangle(bxcf::CPoint2D& vecBottomLeftPoint, float32 fSideLength, float32 fBaseAngle = 0.0f, std::string strStyleGroup = "");	// base angle parameter is in degrees
	CTriangleShape*			addIsoscelesTriangle(bxcf::CPoint2D& vecPosition, float32 fBaseLength, float32 fLegLength, uint32 uiPointingDirection, std::string strStyleGroup = ""); // [parameter uiPointingDirection] Left=1,Top=2,Right=3,Bottom=4,TopLeft=5,TopRight=6,BottomRight=7,BottomLeft=8
	CTriangleShape*			addIsoscelesTriangle(bxcf::CPoint2D& vecBaseCenterPoint, bxcf::CPoint2D& vecTipPoint, uint32 uiBaseHalfWidth, std::string strStyleGroup = "");
	CTriangleShape*			addIsoscelesTriangle(bxcf::CPoint2D& vecBottomLeftPoint, float32 fBaseLength, float32 fTipAngle = 25.0f, float32 fBaseAngle = 0.0f, std::string strStyleGroup = "");	// tip angle parameter is in degrees

	// CGUILayer continued.
	bxcf::CVectorPool<CGUIShape*>*		getShapes(void) { return m_pShapes; }
	bxcf::CVectorPool<CGUIControl*>*	getControls(void) { return m_pControls; }

	CGUIControl*				getControlById(uint32 uiControlId);
	CGUIShape*					getShapeById(uint32 uiShapeId);

	void						setButtonCursorHover(CButtonControl *pButton) { m_pButtonCursorHover = pButton; }
	CButtonControl *			getButtonCursorHover(void) { return m_pButtonCursorHover; }

private:
	void						_addControl(CGUIControl *pWindowControl, bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize, std::string& strStyleGroup);
	void						_addControl(CGUIControl *pWindowControl, std::string& strStyleGroup);
	void						_addShape(CGUIShape *pShape, std::string& strStyleGroup);

	CGUIShape*					createShapeFromId(eGUIShape eShapeId);
	CGUIControl*				createControlFromId(eGUIControl eControlId);

protected:
	CWindow*							m_pWindow;

private:
	bool								m_bEnabled;
	bxcf::CVectorPool<CGUIShape*>*		m_pShapes;
	bxcf::CVectorPool<CGUIControl*>*	m_pControls;
	CButtonControl*						m_pButtonCursorHover;
};

#endif