#ifndef CGUILayer_H
#define CGUILayer_H

#include "Type/Types.h"
#include "Pool/CVectorPool.h"
#include "Shape/CGUIShape.h"
#include "Control/CGUIControl.h"
#include "Type/Vector/CPoint2D.h"
#include "Type/Vector/CSize2D.h"
#include "Event/eEvent.h"
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

class CGUILayer
{
public:
	CGUILayer(void);

	void					unload(void) {}

	void					bindAllEvents(void);
	void					unbindAllEvents(void);

	void					triggerEvent(bxcf::eEvent eEventId, void *pTriggerArgument);

	void					unserialize(void);
	void					serialize(void);

	void					setWindow(CWindow *pWindow) { m_pWindow = pWindow; }
	CWindow*				getWindow(void) { return m_pWindow; }

	void					setEnabled(bool bEnabled);
	bool					isEnabled(void) { return m_bEnabled; }

	CGUIItem*				getItemByPoint(bxcf::CPoint2D& vecPoint);

	// controls
	CGUIControl*			addControl(eGUIControl eControlId, CGUIStyles *pStyles = nullptr);

	CButtonControl*			addButton(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize, std::string strButtonText, CGUIStyles *pStyles = nullptr);
	CCheckControl*			addCheck(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize, std::string strCheckText, CGUIStyles *pStyles = nullptr);
	CDropControl*			addDrop(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize, CGUIStyles *pStyles = nullptr);
	CEditControl*			addEdit(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize, std::string strEditText = "", bool bMultiLine = false, CGUIStyles *pStyles = nullptr);
	CImageControl*			addImage(bxcf::CPoint2D& vecPosition, std::string& strImagePath, bxcf::CSize2D vecSize = bxcf::CSize2D(0, 0), CGUIStyles *pStyles = nullptr);
	// todo CImageControl*			addImageMem(bxcf::CPoint2D& vecPosition, std::string& strImageData, bxcf::CSize2D vecSize = bxcf::CSize2D(0, 0), CGUIStyles *pStyles = nullptr);
	CListControl*			addList(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize, CGUIStyles *pStyles = nullptr);
	CMenuControl*			addMenu(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize, CGUIStyles *pStyles = nullptr);
	CProgressControl*		addProgress(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize, CGUIStyles *pStyles = nullptr);
	CRadioControl*			addRadio(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize, std::string strRadioText, CGUIStyles *pStyles = nullptr);
	CScrollControl*			addScroll(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize, CGUIStyles *pStyles = nullptr);
	CTabControl*			addTabBar(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize, CGUIStyles *pStyles = nullptr);
	CTextControl*			addText(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize, std::string strText, CGUIStyles *pStyles = nullptr);

	CButtonControl*			addButton(int32 x, int32 y, int32 w, int32 h, std::string strButtonText, CGUIStyles *pStyles = nullptr);
	CCheckControl*			addCheck(int32 x, int32 y, int32 w, int32 h, std::string strCheckText, CGUIStyles *pStyles = nullptr);
	CDropControl*			addDrop(int32 x, int32 y, int32 w, int32 h, CGUIStyles *pStyles = nullptr);
	CEditControl*			addEdit(int32 x, int32 y, int32 w, int32 h, std::string strEditText = "", bool bMultiLine = false, CGUIStyles *pStyles = nullptr);
	CImageControl*			addImage(int32 x, int32 y, std::string& strImagePath, int32 w = 0, int32 h = 0, CGUIStyles *pStyles = nullptr);
	CListControl*			addList(int32 x, int32 y, int32 w, int32 h, CGUIStyles *pStyles = nullptr);
	CMenuControl*			addMenu(int32 x, int32 y, int32 w, int32 h, CGUIStyles *pStyles = nullptr);
	CProgressControl*		addProgress(int32 x, int32 y, int32 w, int32 h, CGUIStyles *pStyles = nullptr);
	CRadioControl*			addRadio(int32 x, int32 y, int32 w, int32 h, std::string strRadioText, CGUIStyles *pStyles = nullptr);
	CScrollControl*			addScroll(int32 x, int32 y, int32 w, int32 h, CGUIStyles *pStyles = nullptr);
	CTabControl*			addTabBar(int32 x, int32 y, int32 w, int32 h, CGUIStyles *pStyles = nullptr);
	CTextControl*			addText(int32 x, int32 y, int32 w, int32 h, std::string strText, CGUIStyles *pStyles = nullptr);

	CTextControl*			addText(int32 x, int32 y, int32 w, int32 h, std::string strText, std::string strStyles);

	// shapes
	CGUIShape*				addShape(eGUIShape eShapeId, CGUIStyles *pStyles = nullptr);

	CLineShape*				addLine(bxcf::CPoint2D& vecPoint1, bxcf::CPoint2D& vecPoint2, CGUIStyles *pStyles = nullptr);
	CSquareShape*			addSquare(bxcf::CPoint2D& vecPosition, uint32 uiSideLength, CGUIStyles *pStyles = nullptr);
	CRectangleShape*		addRectangle(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize, CGUIStyles *pStyles = nullptr);
	CCircleShape*			addCircle(bxcf::CPoint2D& vecPosition, uint32 uiRadius, CGUIStyles *pStyles = nullptr);		// position is top left of circle
	CEllipseShape*			addEllipse(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize, CGUIStyles *pStyles = nullptr);
	CPolygonShape*			addPolygon(std::vector<bxcf::CPoint2D>& vecPoints, CGUIStyles *pStyles = nullptr);

	CLineShape*				addLine(int32 x1, int32 y1, int32 x2, int32 y2, CGUIStyles *pStyles = nullptr);
	CSquareShape*			addSquare(int32 x, int32 y, int32 w, CGUIStyles *pStyles = nullptr);
	CRectangleShape*		addRectangle(int32 x, int32 y, int32 w, int32 h, CGUIStyles *pStyles = nullptr);
	CCircleShape*			addCircle(int32 x, int32 y, int32 r, CGUIStyles *pStyles = nullptr);		// position is top left of circle
	CEllipseShape*			addEllipse(int32 x, int32 y, int32 rw, int32 rh, CGUIStyles *pStyles = nullptr);
	
	CTriangleShape*			addTriangle(bxcf::CPoint2D& vecPoint1, bxcf::CPoint2D& vecPoint2, bxcf::CPoint2D& vecPoint3, CGUIStyles *pStyles = nullptr);		// scalene or any triangle type
	CTriangleShape*			addEquilateralTriangle(bxcf::CPoint2D& vecPosition, float32 fSideLength, uint32 uiPointingDirection, CGUIStyles *pStyles = nullptr); // [parameter uiPointingDirection] Left=1,Top=2,Right=3,Bottom=4,TopLeft=5,TopRight=6,BottomRight=7,BottomLeft=8
	CTriangleShape*			addEquilateralTriangle(bxcf::CPoint2D& vecBottomLeftPoint, bxcf::CPoint2D& vecBottomRightPoint, CGUIStyles *pStyles = nullptr);
	CTriangleShape*			addEquilateralTriangle(bxcf::CPoint2D& vecBottomLeftPoint, float32 fSideLength, float32 fBaseAngle = 0.0f, CGUIStyles *pStyles = nullptr);	// base angle parameter is in degrees
	CTriangleShape*			addIsoscelesTriangle(bxcf::CPoint2D& vecPosition, float32 fBaseLength, float32 fLegLength, uint32 uiPointingDirection, CGUIStyles *pStyles = nullptr); // [parameter uiPointingDirection] Left=1,Top=2,Right=3,Bottom=4,TopLeft=5,TopRight=6,BottomRight=7,BottomLeft=8
	CTriangleShape*			addIsoscelesTriangle(bxcf::CPoint2D& vecBaseCenterPoint, bxcf::CPoint2D& vecTipPoint, uint32 uiBaseHalfWidth, CGUIStyles *pStyles = nullptr);
	CTriangleShape*			addIsoscelesTriangle(bxcf::CPoint2D& vecBottomLeftPoint, float32 fBaseLength, float32 fTipAngle = 25.0f, float32 fBaseAngle = 0.0f, CGUIStyles *pStyles = nullptr);	// tip angle parameter is in degrees

	// CGUILayer continued.
	bxcf::CVectorPool<CGUIShape*>&		getShapes(void) { return m_vecShapes; }
	bxcf::CVectorPool<CGUIControl*>&	getControls(void) { return m_vecControls; }

	CGUIControl*				getControlById(uint32 uiControlId);
	CGUIShape*					getShapeById(uint32 uiShapeId);

private:
	void						_addControl(CGUIControl *pWindowControl, bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize, CGUIStyles *pStyles);
	void						_addControl(CGUIControl *pWindowControl, CGUIStyles *pStyles);
	void						_addShape(CGUIShape *pShape, CGUIStyles *pStyles);

	CGUIShape*					createShapeFromId(eGUIShape eShapeId);
	CGUIControl*				createControlFromId(eGUIControl eControlId);

private:
	CWindow*					m_pWindow;
	bool						m_bEnabled;
	bxcf::CVectorPool<CGUIShape*>		m_vecShapes;
	bxcf::CVectorPool<CGUIControl*>	m_vecControls;
};

#endif