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

	void					triggerEvent(mcore::eEvent eEventId, void *pTriggerArgument);

	void					unserialize(void);
	void					serialize(void);

	void					setWindow(CWindow *pWindow) { m_pWindow = pWindow; }
	CWindow*				getWindow(void) { return m_pWindow; }

	void					setEnabled(bool bEnabled);
	bool					isEnabled(void) { return m_bEnabled; }

	CGUIItem*				getItemByPoint(mcore::CPoint2D& vecPoint);

	// controls
	CGUIControl*			addControl(eGUIControl eControlId, CGUIStyles *pStyles = nullptr);

	CButtonControl*			addButton(mcore::CPoint2D& vecPosition, mcore::CSize2D& vecSize, std::string strButtonText, CGUIStyles *pStyles = nullptr);
	CCheckControl*			addCheck(mcore::CPoint2D& vecPosition, mcore::CSize2D& vecSize, std::string strCheckText, CGUIStyles *pStyles = nullptr);
	CDropControl*			addDrop(mcore::CPoint2D& vecPosition, mcore::CSize2D& vecSize, CGUIStyles *pStyles = nullptr);
	CEditControl*			addEdit(mcore::CPoint2D& vecPosition, mcore::CSize2D& vecSize, std::string strEditText = "", bool bMultiLine = false, CGUIStyles *pStyles = nullptr);
	CImageControl*			addImage(mcore::CPoint2D& vecPosition, std::string& strImagePath, mcore::CSize2D vecSize = mcore::CSize2D(0, 0), CGUIStyles *pStyles = nullptr);
	// todo CImageControl*			addImageMem(mcore::CPoint2D& vecPosition, std::string& strImageData, mcore::CSize2D vecSize = mcore::CSize2D(0, 0), CGUIStyles *pStyles = nullptr);
	CListControl*			addList(mcore::CPoint2D& vecPosition, mcore::CSize2D& vecSize, CGUIStyles *pStyles = nullptr);
	CMenuControl*			addMenu(mcore::CPoint2D& vecPosition, mcore::CSize2D& vecSize, CGUIStyles *pStyles = nullptr);
	CProgressControl*		addProgress(mcore::CPoint2D& vecPosition, mcore::CSize2D& vecSize, CGUIStyles *pStyles = nullptr);
	CRadioControl*			addRadio(mcore::CPoint2D& vecPosition, mcore::CSize2D& vecSize, std::string strRadioText, CGUIStyles *pStyles = nullptr);
	CScrollControl*			addScroll(mcore::CPoint2D& vecPosition, mcore::CSize2D& vecSize, CGUIStyles *pStyles = nullptr);
	CTabControl*			addTabBar(mcore::CPoint2D& vecPosition, mcore::CSize2D& vecSize, CGUIStyles *pStyles = nullptr);
	CTextControl*			addText(mcore::CPoint2D& vecPosition, mcore::CSize2D& vecSize, std::string strText, CGUIStyles *pStyles = nullptr);

	// shapes
	CGUIShape*				addShape(eGUIShape eShapeId, CGUIStyles *pStyles = nullptr);

	CLineShape*				addLine(mcore::CPoint2D& vecPoint1, mcore::CPoint2D& vecPoint2, CGUIStyles *pStyles = nullptr);
	CRectangleShape*		addRectangle(mcore::CPoint2D& vecPosition, mcore::CSize2D& vecSize, CGUIStyles *pStyles = nullptr);
	CEllipseShape*			addEllipse(mcore::CPoint2D& vecPosition, mcore::CSize2D& vecSize, CGUIStyles *pStyles = nullptr);
	CPolygonShape*			addPolygon(std::vector<mcore::CPoint2D>& vecPoints, CGUIStyles *pStyles = nullptr);

	CSquareShape*			addSquare(mcore::CPoint2D& vecPosition, uint32 uiSideLength, CGUIStyles *pStyles = nullptr);
	CCircleShape*			addCircle(mcore::CPoint2D& vecPosition, uint32 uiRadius, CGUIStyles *pStyles = nullptr);		// position is top left of circle
	CTriangleShape*			addTriangle(mcore::CPoint2D& vecPoint1, mcore::CPoint2D& vecPoint2, mcore::CPoint2D& vecPoint3, CGUIStyles *pStyles = nullptr);		// scalene or any triangle type
	CTriangleShape*			addEquilateralTriangle(mcore::CPoint2D& vecPosition, float32 fSideLength, uint32 uiPointingDirection, CGUIStyles *pStyles = nullptr); // [parameter uiPointingDirection] Left=1,Top=2,Right=3,Bottom=4,TopLeft=5,TopRight=6,BottomRight=7,BottomLeft=8
	CTriangleShape*			addEquilateralTriangle(mcore::CPoint2D& vecBottomLeftPoint, mcore::CPoint2D& vecBottomRightPoint, CGUIStyles *pStyles = nullptr);
	CTriangleShape*			addEquilateralTriangle(mcore::CPoint2D& vecBottomLeftPoint, float32 fSideLength, float32 fBaseAngle = 0.0f, CGUIStyles *pStyles = nullptr);	// base angle parameter is in degrees
	CTriangleShape*			addIsoscelesTriangle(mcore::CPoint2D& vecPosition, float32 fBaseLength, float32 fLegLength, uint32 uiPointingDirection, CGUIStyles *pStyles = nullptr); // [parameter uiPointingDirection] Left=1,Top=2,Right=3,Bottom=4,TopLeft=5,TopRight=6,BottomRight=7,BottomLeft=8
	CTriangleShape*			addIsoscelesTriangle(mcore::CPoint2D& vecBaseCenterPoint, mcore::CPoint2D& vecTipPoint, uint32 uiBaseHalfWidth, CGUIStyles *pStyles = nullptr);
	CTriangleShape*			addIsoscelesTriangle(mcore::CPoint2D& vecBottomLeftPoint, float32 fBaseLength, float32 fTipAngle = 25.0f, float32 fBaseAngle = 0.0f, CGUIStyles *pStyles = nullptr);	// tip angle parameter is in degrees

	// CGUILayer continued.
	mcore::CVectorPool<CGUIShape*>&		getShapes(void) { return m_vecShapes; }
	mcore::CVectorPool<CGUIControl*>&	getControls(void) { return m_vecControls; }

	CGUIControl*				getControlById(uint32 uiControlId);
	CGUIShape*					getShapeById(uint32 uiShapeId);

private:
	void						_addControl(CGUIControl *pWindowControl, mcore::CPoint2D& vecPosition, mcore::CSize2D& vecSize, CGUIStyles *pStyles);
	void						_addControl(CGUIControl *pWindowControl, CGUIStyles *pStyles);
	void						_addShape(CGUIShape *pShape, CGUIStyles *pStyles);

	CGUIShape*					createShapeFromId(eGUIShape eShapeId);
	CGUIControl*				createControlFromId(eGUIControl eControlId);

private:
	CWindow*					m_pWindow;
	bool						m_bEnabled;
	mcore::CVectorPool<CGUIShape*>		m_vecShapes;
	mcore::CVectorPool<CGUIControl*>	m_vecControls;
};

#endif