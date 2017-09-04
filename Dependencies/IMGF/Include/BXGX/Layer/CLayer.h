#pragma once

#include "nsbxgx.h"
#include "Type/Types.h"
#include "Pool/CVectorPool.h"
#include "Shape/CShape.h"
#include "Control/Control.h"
#include "Control/EControl.h"
#include "Type/Vector/Vec2i.h"
#include "Type/Vector/Vec2u.h"
#include "Renderable/CRenderable.h"
#include "Renderable/ERenderable.h"
#include "Layer/ELayerType.h"
#include <string>
#include <vector>

class bxgx::CCircle;
class bxgx::CEllipse;
class bxgx::CLine;
class bxgx::CPolygon;
class bxgx::CRectangle;
class bxgx::CSquare;
class bxgx::CTriangle;

class bxgx::CButton;
class bxgx::CCheckBox;
class bxgx::CDropDown;
class bxgx::CTextBox;
class bxgx::CImage;
class bxgx::CGrid;
class bxgx::CMenu;
class bxgx::CProgressBar;
class bxgx::CRadioButton;
class bxgx::CScrollBar;
class bxgx::CTabBar;
class bxgx::CText;

class bxgx::CLayerItem;

class bxgx::CLayer : public CRenderable
{
public:
	CLayer(void);

	void					unload(void) {}

	void					bindEvents(void);
	void					unbindEvents(void);

	void					bindItemEvents(void);
	void					unbindItemEvents(void);

	void					unserialize(void);
	void					serialize(void);

	bxgx::item::ERenderable	getItemType(void) { return bxgx::item::LAYER; }
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

	void					setZIndex(int32 iZIndex) { m_iZIndex = iZIndex; }
	int32					getZIndex(void) { return m_iZIndex; }

	CLayerItem*				getItemByPoint(bxcf::Vec2i& vecPoint, bxgx::EControl eControlType = UNKNOWN_CONTROL);

	// controls
	bxgx::Control*			addControl(bxgx::EControl eControlId, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	void					removeControl(bxgx::Control *pControl);

	CButton*			addButton(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize, std::string strButtonText, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	CCheckBox*			addCheck(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize, std::string strCheckText, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	CDropDown*			addDrop(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize, std::string strDefaultText, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	CImage*			addImage(bxcf::Vec2i& vecPosition, std::string strImagePath, bxcf::Vec2u vecSize = bxcf::Vec2u(0, 0), std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	// todo CImage*			addImageMem(bxcf::Vec2i& vecPosition, std::string& strImageData, bxcf::Vec2u vecSize = bxcf::Vec2u(0, 0), std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	CGrid*			addGrid(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	CMenu*			addMenu(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	CProgressBar*		addProgress(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	CRadioButton*			addRadio(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize, std::string strRadioText, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	CScrollBar*			addScroll(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	CTabBar*			addTabBar(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	CText*			addText(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize, std::string strText, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	CTextBox*		addTextBox(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize, std::string strText = "", bool bMultiLine = false, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);

	CButton*			addButton(int32 x, int32 y, int32 w, int32 h, std::string strButtonText, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	CCheckBox*			addCheck(int32 x, int32 y, int32 w, int32 h, std::string strCheckText, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	CDropDown*			addDrop(int32 x, int32 y, int32 w, int32 h, std::string strDefaultText, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	CImage*			addImage(int32 x, int32 y, std::string strImagePath, int32 w = 0, int32 h = 0, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	CGrid*			addGrid(int32 x, int32 y, int32 w, int32 h, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	CMenu*			addMenu(int32 x, int32 y, int32 w, int32 h, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	CProgressBar*		addProgress(int32 x, int32 y, int32 w, int32 h, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	CRadioButton*			addRadio(int32 x, int32 y, int32 w, int32 h, std::string strRadioText, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	CScrollBar*			addScroll(int32 x, int32 y, int32 w, int32 h, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	CTabBar*			addTabBar(int32 x, int32 y, int32 w, int32 h, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	CText*			addText(int32 x, int32 y, int32 w, int32 h, std::string strText, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	CTextBox*		addTextBox(int32 x, int32 y, int32 w, int32 h, std::string strText = "", bool bMultiLine = false, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);

	//CText*			addText(int32 x, int32 y, int32 w, int32 h, std::string strText, std::string strStyles);

	// shapes
	CShape*				addShape(EShape eShapeId, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	void					removeShape(CShape *pShape);

	CLine*				addLine(bxcf::Vec2i& vecPoint1, bxcf::Vec2i& vecPoint2, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	CSquare*			addSquare(bxcf::Vec2i& vecPosition, uint32 uiSideLength, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	CRectangle*		addRectangle(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	CCircle*			addCircle(bxcf::Vec2i& vecPosition, uint32 uiRadius, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);		// position is top left of circle
	CEllipse*			addEllipse(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	CPolygon*			addPolygon(std::vector<bxcf::Vec2i>& vecPoints, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);

	CLine*				addLine(int32 x1, int32 y1, int32 x2, int32 y2, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	CSquare*			addSquare(int32 x, int32 y, int32 w, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	CRectangle*		addRectangle(int32 x, int32 y, int32 w, int32 h, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	CCircle*			addCircle(int32 x, int32 y, int32 r, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);		// position is top left of circle
	CEllipse*			addEllipse(int32 x, int32 y, int32 rw, int32 rh, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	
	CTriangle*			addTriangle(bxcf::Vec2i& vecPoint1, bxcf::Vec2i& vecPoint2, bxcf::Vec2i& vecPoint3, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);		// scalene or any triangle type
	CTriangle*			addEquilateralTriangle(bxcf::Vec2i& vecPosition, float32 fSideLength, uint32 uiPointingDirection, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0); // [parameter uiPointingDirection] Left=1,Top=2,Right=3,Bottom=4,TopLeft=5,TopRight=6,BottomRight=7,BottomLeft=8
	CTriangle*			addEquilateralTriangle(bxcf::Vec2i& vecBottomLeftPoint, bxcf::Vec2i& vecBottomRightPoint, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	CTriangle*			addEquilateralTriangle(bxcf::Vec2i& vecBottomLeftPoint, float32 fSideLength, float32 fBaseAngle = 0.0f, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);	// base angle parameter is in degrees
	CTriangle*			addIsoscelesTriangle(bxcf::Vec2i& vecPosition, float32 fBaseLength, float32 fLegLength, uint32 uiPointingDirection, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0); // [parameter uiPointingDirection] Left=1,Top=2,Right=3,Bottom=4,TopLeft=5,TopRight=6,BottomRight=7,BottomLeft=8
	CTriangle*			addIsoscelesTriangle(bxcf::Vec2i& vecBaseCenterPoint, bxcf::Vec2i& vecTipPoint, uint32 uiBaseHalfWidth, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	CTriangle*			addIsoscelesTriangle(bxcf::Vec2i& vecBottomLeftPoint, float32 fBaseLength, float32 fTipAngle = 25.0f, float32 fBaseAngle = 0.0f, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);	// tip angle parameter is in degrees

	// CLayer continued.
	bxcf::CVectorPool<CShape*>*		getShapes(void) { return m_pShapes; }
	bxcf::CVectorPool<bxgx::Control*>*	getControls(void) { return m_pControls; }

	bxgx::Control*				getControlById(uint32 uiControlId);
	CShape*					getShapeById(uint32 uiShapeId);

	void						setDropWithListOpen(CDropDown *pDrop) { m_pDropWithListOpen = pDrop; }
	CDropDown*				getDropWithListOpen(void) { return m_pDropWithListOpen; }
	void						clearDropWithListOpen(void) { m_pDropWithListOpen = nullptr; }

	void						render(void);

private:
	void						initializeControl(bxgx::Control *pWindowControl, bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize, std::string& strStyleGroups, uint32 uiItemId, int32 iZIndex = 0);
	void						initializeControl(bxgx::Control *pWindowControl, std::string& strStyleGroups, uint32 uiItemId, int32 iZIndex = 0);
	void						initializeShape(CShape *pShape, std::string& strStyleGroups, uint32 uiItemId, int32 iZIndex = 0);

	uint32						getControlInsertionIndex(int32 iZIndex);
	uint32						getShapeInsertionIndex(int32 iZIndex);

	CShape*					createShapeFromId(EShape eShapeId);
	bxgx::Control*				createControlFromId(bxgx::EControl eControlId);

protected:
	CWindow*							m_pWindow;

private:
	bool								m_bEnabled;
	CDropDown*						m_pDropWithListOpen;
	uint32								m_uiId;
	int32								m_iZIndex;
	bxcf::CVectorPool<CShape*>*		m_pShapes;
	bxcf::CVectorPool<bxgx::Control*>*	m_pControls;
};