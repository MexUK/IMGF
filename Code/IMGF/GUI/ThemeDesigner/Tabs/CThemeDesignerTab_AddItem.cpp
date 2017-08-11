#include "CThemeDesignerTab_AddItem.h"
#include "Math/CMath.h"
#include "Event/CEventManager.h"
#include "Event/eEvent.h"
#include "Input/CInputManager.h"
#include "Styles/CGUIStyles.h"
#include "Shapes/CRectangleShape.h"
#include "Shapes/Geometries/CGUIShapeGeometry_1xPoint_1x1DSize.h"
#include "Shapes/Geometries/CGUIShapeGeometry_1xPoint_1x2DSize.h"
#include "Shapes/Geometries/CGUIShapeGeometry_2xPoints.h" // todo - rename Point to Points
#include "Shapes/Geometries/CGUIShapeGeometry_3xPoints.h" // todo - rename Point to Points
#include "Shapes/Geometries/CGUIShapeGeometry_NxPoints.h" // todo - rename Point to Points
#include "Controls/CCheckControl.h"
#include "Controls/CProgressControl.h"
#include "Controls/CRadioControl.h"
#include "Controls/CDropControl.h"
#include "GUI/ThemeDesigner/CThemeDesigner.h"
#include "Type/Colour/CColour.h"
#include "CIMGF.h"
#include "GUI/ThemeDesigner/CThemeDesigner.h"

using namespace std;
using namespace bxcf;

auto pOnLeftMouseDown_ThemeDesigner				= [](void *pThemeDesigner, void *pTriggerArg) { ((CThemeDesignerTab_AddItem*) pThemeDesigner)->onLeftMouseDown(*(Vec2i*) pTriggerArg); };
auto pOnMouseMove_ThemeDesigner					= [](void *pThemeDesigner, void *pTriggerArg) { ((CThemeDesignerTab_AddItem*) pThemeDesigner)->onMouseMove(*(Vec2i*) pTriggerArg); };
auto pOnLeftMouseDown_ThemeDesigner_MainWindow	= [](void *pThemeDesigner, void *pTriggerArg) { ((CThemeDesignerTab_AddItem*) pThemeDesigner)->onLeftMouseDown_MainWindow(*(Vec2i*) pTriggerArg); };
auto pOnLeftMouseDown_ThemeDesigner_MainWindow_WindowEventType	= [](void *pThemeDesigner, void *pTriggerArg) { ((CThemeDesignerTab_AddItem*) pThemeDesigner)->onLeftMouseDown_MainWindow_WindowEventType(*(Vec2i*) pTriggerArg); };

CThemeDesignerTab_AddItem::CThemeDesignerTab_AddItem(CThemeDesigner *pThemeDesigner) :
	CThemeDesignerTab(pThemeDesigner),
	m_uiHoveredItemType(0),
	m_uiActiveItemType(0),
	m_eHoveredShapeId(GUI_SHAPE_UNKNOWN),
	m_eHoveredControlId(GUI_CONTROL_UNKNOWN),
	m_eActiveShapeId(GUI_SHAPE_UNKNOWN),
	m_eActiveControlId(GUI_CONTROL_UNKNOWN),
	m_uiItemRowHeight(0)
{
}

// event binding
void									CThemeDesignerTab_AddItem::bindEvents(void)
{
	getThemeDesigner()->getWindow()->bindEvent(EVENT_onLeftMouseDown, pOnLeftMouseDown_ThemeDesigner, this);
	getThemeDesigner()->getWindow()->bindEvent(EVENT_onMouseMove, pOnMouseMove_ThemeDesigner, this);

	CEventManager *pEventManager = CEventManager::get();
	CWindow *pMainWindow = bxgx::CGUIManager::get()->getEntryByIndex(1);
	pEventManager->bindEvent(EVENT_TYPE_THEME_DESIGNER, (uint32) pMainWindow->getWindowHandle(), EVENT_onLeftMouseDown, pOnLeftMouseDown_ThemeDesigner_MainWindow, this);

	pMainWindow->bindEvent(EVENT_onLeftMouseDown, pOnLeftMouseDown_ThemeDesigner_MainWindow_WindowEventType, this);
}

// design
void									CThemeDesignerTab_AddItem::initDesign(void)
{
	/*
	setShapeIconStartPosition(Vec2i((int32) 30, 120));
	setShapeTextStartPosition(Vec2i((int32) 60, 120));
	setControlIconStartPosition(Vec2i((int32) (250 + 30), 120));
	setControlTextStartPosition(Vec2i((int32) (250 + 60), 120));
	setItemRowSize(Vec2u(210, 30));
	setItemSize(Vec2u(210, 16));

	CThemeDesigner *pThemeDesigner = getThemeDesigner();

	// add layer
	CGUILayer *pLayer = pThemeDesigner->addLayer("add_item", true);

	// prepare variables
	CGUIShape *pShape = nullptr;
	CGUIControl *pControl = nullptr;

	// fetch window positions and sizes
	Vec2u vecWindowSize = pThemeDesigner->getWindow()->getSize();
	Vec2i vecWindowCenterPosition = Vec2i(vecWindowSize.x, vecWindowSize.y) / 2;
	uint32 uiCenterX = CMath::getCenterX(vecWindowSize.x);

	// create styles
	CGUIStyles
		*pStyles_GoldBorder = bxgx::CGUIManager::createStyles(),
		*pStyles_GoldText = bxgx::CGUIManager::createStyles(),
		*pStyles_BlueBorder = bxgx::CGUIManager::createStyles(),
		*pStyles_BlueText = bxgx::CGUIManager::createStyles(),
		*pStyles_Edit = bxgx::CGUIManager::createStyles(),
		*pStyles_BlueBorderAndText = bxgx::CGUIManager::createStyles(),
		*pStyles_Progress = bxgx::CGUIManager::createStyles(),
		*pStyles_Radio = bxgx::CGUIManager::createStyles();

	pStyles_GoldBorder->setStyle("border-colour", CColour(230, 223, 12));
	pStyles_GoldText->setStyle("text-colour", CColour(230, 223, 12));
	pStyles_BlueBorder->setStyle("border-colour", CColour(121, 180, 199));
	pStyles_BlueText->setStyle("text-colour", CColour(121, 180, 199));
	pStyles_Edit->setStyle("border-colour", CColour(121, 180, 199));
	pStyles_Edit->setStyle("fill-colour", CColour(0xFF, 0xFF, 0xFF));
	pStyles_BlueBorderAndText->setStyle("border-colour", CColour(121, 180, 199));
	pStyles_BlueBorderAndText->setStyle("text-colour", CColour(121, 180, 199));
	pStyles_Progress->setStyle("border-colour", CColour(121, 180, 199));
	pStyles_Progress->setStyle("progress-bar-fill-colour", CColour(85, 33, 33));
	pStyles_Radio->setStyle<CColour>("border-colour", CColour(121, 180, 199));
	pStyles_Radio->setStyle<CColour>("fill-colour:marked", CColour(85, 33, 33));

	// add 2 lines
	pShape = (CGUIShape*) pLayer->addLine(Vec2i((int32) 0, 80), Vec2i(vecWindowSize.x, 80), pStyles_GoldBorder);					// horizontal line
	pShape = (CGUIShape*) pLayer->addLine(Vec2i(uiCenterX, 25), Vec2i(uiCenterX, vecWindowSize.y), pStyles_GoldBorder);	// vertical line
	
	// add headers
	pControl = (CGUIControl*) pLayer->addText(Vec2i((int32) 20, 50), Vec2u(150, 30), "Shapes", pStyles_GoldText);
	pControl = (CGUIControl*) pLayer->addText(Vec2i(uiCenterX + 20, 50), Vec2u(150, 30), "Controls", pStyles_GoldText);

	// prepare shape icons and text
	uint32
		uiShapeIconX = getShapeIconStartPosition().x,
		uiShapeTextX = getShapeTextStartPosition().x,
		uiShapeIconY = getShapeIconStartPosition().y;

	vector<Vec2i> vecPolygonPoints;
	vecPolygonPoints.resize(5);
	vecPolygonPoints[0] = Vec2i(uiShapeIconX, uiShapeIconY + 90);
	vecPolygonPoints[1] = Vec2i(uiShapeIconX + 15, uiShapeIconY + 90 + 3);
	vecPolygonPoints[2] = Vec2i(uiShapeIconX + 12, uiShapeIconY + 90 + 10);
	vecPolygonPoints[3] = Vec2i(uiShapeIconX + 7, uiShapeIconY + 90 + 5);
	vecPolygonPoints[4] = Vec2i(uiShapeIconX + 4, uiShapeIconY + 90 + 15);

	// add shape icons
	pShape = (CGUIShape*) pLayer->addCircle(				Vec2i(uiShapeIconX, uiShapeIconY),			7, pStyles_BlueBorder); // todo - make addCircle take a float for radius coz diameter might be odd number
	pShape = (CGUIShape*) pLayer->addEllipse(				Vec2i(uiShapeIconX + 3, uiShapeIconY + 30),	Vec2u(8, 14), pStyles_BlueBorder);
	pShape = (CGUIShape*) pLayer->addLine(					Vec2i(uiShapeIconX, uiShapeIconY + 60),		Vec2i(uiShapeIconX + 15, 120 + 60 + 15), pStyles_BlueBorder);
	pShape = (CGUIShape*) pLayer->addPolygon(vecPolygonPoints, pStyles_BlueBorder);
	pShape = (CGUIShape*) pLayer->addRectangle(				Vec2i(uiShapeIconX + 3, uiShapeIconY + 120),	Vec2u(8, 15), pStyles_BlueBorder);
	pShape = (CGUIShape*) pLayer->addSquare(				Vec2i(uiShapeIconX, uiShapeIconY + 150),		15, pStyles_BlueBorder);
	pShape = (CGUIShape*) pLayer->addEquilateralTriangle(	Vec2i(uiShapeIconX, uiShapeIconY + 195),		15.0f, 0.0f, pStyles_BlueBorder);

	// add shape text
	pControl = (CGUIControl*) pLayer->addText(Vec2i(uiShapeTextX, uiShapeIconY), Vec2u(150, 30), "Circle", pStyles_BlueText);
	pControl = (CGUIControl*) pLayer->addText(Vec2i(uiShapeTextX, uiShapeIconY + 30), Vec2u(150, 30), "Ellipse", pStyles_BlueText);
	pControl = (CGUIControl*) pLayer->addText(Vec2i(uiShapeTextX, uiShapeIconY + 60), Vec2u(150, 30), "Line", pStyles_BlueText);
	pControl = (CGUIControl*) pLayer->addText(Vec2i(uiShapeTextX, uiShapeIconY + 90), Vec2u(150, 30), "Polygon", pStyles_BlueText);
	pControl = (CGUIControl*) pLayer->addText(Vec2i(uiShapeTextX, uiShapeIconY + 120), Vec2u(150, 30), "Rectangle", pStyles_BlueText);
	pControl = (CGUIControl*) pLayer->addText(Vec2i(uiShapeTextX, uiShapeIconY + 150), Vec2u(150, 30), "Square", pStyles_BlueText);
	pControl = (CGUIControl*) pLayer->addText(Vec2i(uiShapeTextX, uiShapeIconY + 180), Vec2u(150, 30), "Triangle", pStyles_BlueText);

	// prepare control icons and text
	uint32
		uiControlIconX = uiCenterX + 30,
		uiControlTextX = uiCenterX + 60,
		uiControlIconY = 120;

	// add control icons
	pControl = (CGUIControl*) pLayer->addButton(Vec2i(uiControlIconX, uiControlIconY), Vec2u(15, 9), "", pStyles_BlueBorder);

	pControl = (CGUIControl*) pLayer->addCheck(Vec2i(uiControlIconX, uiControlIconY + 30), Vec2u(15, 15), "", pStyles_BlueBorder);
	((CCheckControl*) pControl)->setMarked(true);

	pControl = (CGUIControl*) pLayer->addDrop(Vec2i(uiControlIconX, uiControlIconY + 60), Vec2u(15, 10), pStyles_BlueBorder);

	pControl = (CGUIControl*) pLayer->addTextBox(Vec2i(uiControlIconX, uiControlIconY + 90), Vec2u(15, 15), "", true, pStyles_Edit);
	pControl = (CGUIControl*) pLayer->addList(Vec2i(uiControlIconX, uiControlIconY + 120), Vec2u(15, 15), pStyles_BlueBorder);
	// todo pControl = (CGUIControl*) pLayer->addMenu(Vec2i(uiControlIconX, uiControlIconY + 150), Vec2u(15, 15), pStyles_BlueBorder);

	pControl = (CGUIControl*) pLayer->addProgress(Vec2i(uiControlIconX, uiControlIconY + 180), Vec2u(15, 12), pStyles_Progress);
	((CProgressControl*) pControl)->setProgress(0.7);
	((CProgressControl*) pControl)->setCompletionPercentageShown(false);

	pControl = (CGUIControl*) pLayer->addRadio(Vec2i(uiControlIconX, uiControlIconY + 210), Vec2u(15, 15), "", pStyles_Radio);
	((CRadioControl*) pControl)->setMarked(true);

	pControl = (CGUIControl*) pLayer->addScroll(Vec2i(uiControlIconX, uiControlIconY + 240), Vec2u(10, 15), pStyles_BlueBorder);
	// todo pControl = (CGUIControl*) pLayer->addTabs(Vec2i(uiControlIconX, uiControlIconY + 270), Vec2u(15, 15), "Tabs", pStyles_BlueBorder);
	pControl = (CGUIControl*) pLayer->addText(Vec2i(uiControlIconX, uiControlIconY + 300), Vec2u(15, 15), "abc", pStyles_BlueBorderAndText);

	// add control text
	pControl = (CGUIControl*) pLayer->addText(Vec2i(uiControlTextX, uiControlIconY), Vec2u(150, 30), "Button", pStyles_BlueText);
	pControl = (CGUIControl*) pLayer->addText(Vec2i(uiControlTextX, uiControlIconY + 30), Vec2u(150, 30), "Check", pStyles_BlueText);
	pControl = (CGUIControl*) pLayer->addText(Vec2i(uiControlTextX, uiControlIconY + 60), Vec2u(150, 30), "Drop", pStyles_BlueText);
	pControl = (CGUIControl*) pLayer->addText(Vec2i(uiControlTextX, uiControlIconY + 90), Vec2u(150, 30), "Edit", pStyles_BlueText);
	pControl = (CGUIControl*) pLayer->addText(Vec2i(uiControlTextX, uiControlIconY + 120), Vec2u(150, 30), "List", pStyles_BlueText);
	pControl = (CGUIControl*) pLayer->addText(Vec2i(uiControlTextX, uiControlIconY + 150), Vec2u(150, 30), "Menu", pStyles_BlueText);
	pControl = (CGUIControl*) pLayer->addText(Vec2i(uiControlTextX, uiControlIconY + 180), Vec2u(150, 30), "Progress", pStyles_BlueText);
	pControl = (CGUIControl*) pLayer->addText(Vec2i(uiControlTextX, uiControlIconY + 210), Vec2u(150, 30), "Radio", pStyles_BlueText);
	pControl = (CGUIControl*) pLayer->addText(Vec2i(uiControlTextX, uiControlIconY + 240), Vec2u(150, 30), "Scroll", pStyles_BlueText);
	pControl = (CGUIControl*) pLayer->addText(Vec2i(uiControlTextX, uiControlIconY + 270), Vec2u(150, 30), "Tabs", pStyles_BlueText);
	pControl = (CGUIControl*) pLayer->addText(Vec2i(uiControlTextX, uiControlIconY + 300), Vec2u(150, 30), "Text", pStyles_BlueText);
	*/
}

// input - theme designer window
void									CThemeDesignerTab_AddItem::onLeftMouseDown(Vec2i& vecCursorPosition)
{
	/*
	getIMGF()->getThemeDesigner()->setThemeDesignerModeEnabled(true);
	bxgx::CGUIManager::get()->getEntryByIndex(1)->setMarkedToRedraw(true); // redraw main window title bar

	uint32
		uiShapeIndex,
		uiControlIndex;
	Vec2i
		vecRectanglePosition;
	Vec2u
		vecRectangleSize(210, 30); // todo - move to object property
	bool
		bShowRectangle = false;

	uiShapeIndex = getTabShapeIndexFromPoint(vecCursorPosition);
	if (uiShapeIndex == -1)
	{
		uiControlIndex = getTabControlIndexFromPoint(vecCursorPosition);

		if (uiControlIndex != -1)
		{
			// mouse is over a control row
			vecRectanglePosition = getControlRowPoint(uiControlIndex); // todo getControlRowSize(ui)
			setActiveItemType(2); // control
			setActiveControlId(getControlIdFromIndex(uiControlIndex));
			bShowRectangle = true;
		}
	}
	else
	{
		// mouse over a shape row
		vecRectanglePosition = getShapeRowPoint(uiShapeIndex); // todo getShapeRowSize(ui)
		setActiveItemType(1); // shape
		setActiveShapeId(getShapeIdFromIndex(uiShapeIndex));
		bShowRectangle = true;
	}

	if (bShowRectangle)
	{
		if (getThemeDesigner()->getActiveItemRectangle() != nullptr)
		{
			getThemeDesigner()->getActiveItemRectangle()->unbindEvents();
			getThemeDesigner()->getActiveItemRectangle()->getLayer()->getShapes()->removeEntry(getThemeDesigner()->getActiveItemRectangle());
			getThemeDesigner()->setActiveItemRectangle(nullptr);
			getThemeDesigner()->getWindow()->setMarkedToRedraw(true);
		}

		CGUIStyles *pStyles = new CGUIStyles;
		pStyles->setStyle("fill-colour", CColour(215, 0, 0, 50));
		pStyles->setStyle("border-colour", CColour(255, 0, 0, 230));
		getThemeDesigner()->setActiveItemRectangle(getThemeDesigner()->m_umapTabLayers["add_item"]->addRectangle(vecRectanglePosition, vecRectangleSize, pStyles));
		getThemeDesigner()->getActiveItemRectangle()->bindEvents();
		getThemeDesigner()->getWindow()->setMarkedToRedraw(true);
	}
	else
	{
		if (getThemeDesigner()->getActiveItemRectangle() != nullptr)
		{
			getThemeDesigner()->getActiveItemRectangle()->unbindEvents();
			getThemeDesigner()->getActiveItemRectangle()->getLayer()->getShapes()->removeEntry(getThemeDesigner()->getActiveItemRectangle());
			getThemeDesigner()->setActiveItemRectangle(nullptr);
			getThemeDesigner()->getWindow()->setMarkedToRedraw(true);
		}

		getIMGF()->getThemeDesigner()->setThemeDesignerModeEnabled(false);
	}
	*/
}

void									CThemeDesignerTab_AddItem::onMouseMove(Vec2i& vecCursorPosition)
{
	/*
	uint32
		uiShapeIndex,
		uiControlIndex;
	Vec2i
		vecRectanglePosition;
	Vec2u
		vecRectangleSize(210, 30); // todo - move to object property
	bool
		bShowRectangle = false;

	uiShapeIndex = getTabShapeIndexFromPoint(vecCursorPosition);
	if (uiShapeIndex == -1)
	{
		uiControlIndex = getTabControlIndexFromPoint(vecCursorPosition);

		if (uiControlIndex != -1)
		{
			// mouse is over a control row
			vecRectanglePosition = getControlRowPoint(uiControlIndex); // todo getControlRowSize(ui)
			setHoveredItemType(2); // control
			setHoveredControlId(getControlIdFromIndex(uiControlIndex));
			bShowRectangle = true;
		}
	}
	else
	{
		// mouse over a shape row
		vecRectanglePosition = getShapeRowPoint(uiShapeIndex); // todo getShapeRowSize(ui)
		setHoveredItemType(1); // shape
		setHoveredShapeId(getShapeIdFromIndex(uiShapeIndex));
		bShowRectangle = true;
	}

	if (bShowRectangle)
	{
		if (getThemeDesigner()->getItemHoverRectangle() != nullptr)
		{
			getThemeDesigner()->getItemHoverRectangle()->unbindEvents();
			getThemeDesigner()->getItemHoverRectangle()->getLayer()->getShapes()->removeEntry(getThemeDesigner()->getItemHoverRectangle());
			getThemeDesigner()->setItemHoverRectangle(nullptr);
			getThemeDesigner()->getWindow()->setMarkedToRedraw(true);
		}

		CGUIStyles *pStyles = new CGUIStyles;
		pStyles->setStyle("fill-colour", CColour(215, 0, 0, 50));
		getThemeDesigner()->setItemHoverRectangle(getThemeDesigner()->m_umapTabLayers["add_item"]->addRectangle(vecRectanglePosition, vecRectangleSize, pStyles));
		getThemeDesigner()->getItemHoverRectangle()->bindEvents();
		getThemeDesigner()->getWindow()->setMarkedToRedraw(true);
	}
	else
	{
		if (getThemeDesigner()->getItemHoverRectangle() != nullptr)
		{
			getThemeDesigner()->getItemHoverRectangle()->unbindEvents();
			getThemeDesigner()->getItemHoverRectangle()->getLayer()->getShapes()->removeEntry(getThemeDesigner()->getItemHoverRectangle());
			getThemeDesigner()->setItemHoverRectangle(nullptr);
			getThemeDesigner()->getWindow()->setMarkedToRedraw(true);
		}
	}
	*/
}

// input - main window
void									CThemeDesignerTab_AddItem::onLeftMouseDown_MainWindow(Vec2i& vecCursorPosition)
{
	/*
	CWindow *pMainWindow = bxgx::CGUIManager::get()->getEntryByIndex(1);

	uint32 uiAddItemType = getActiveItemType();
	if (uiAddItemType != 0)
	{
		// add shape or control
		CGUILayer *pLayer = pMainWindow->getEntryByIndex(0);

		CGUIStyles *pDefaultItemStyles = new CGUIStyles;
		pDefaultItemStyles->setStyle("border-colour", CColour(0, 0, 0));

		if (uiAddItemType == 1)
		{
			// shape
			CGUIShape *pShape = pLayer->addShape(getActiveShapeId(), pDefaultItemStyles);
			switch (pShape->getShapeGeometry())
			{
			case GUI_SHAPE_GEOMETRY_1_POINT_1_X_1D_SIZE: // circle, square
				((CGUIShapeGeometry_1xPoint_1x1DSize*) pShape)->setPosition(vecCursorPosition);
				((CGUIShapeGeometry_1xPoint_1x1DSize*) pShape)->setSize(7.5);
				break;
			case GUI_SHAPE_GEOMETRY_1_POINT_1_X_2D_SIZE: // ellipse, rectangle
				((CGUIShapeGeometry_1xPoint_1x2DSize*) pShape)->setPosition(vecCursorPosition);
				((CGUIShapeGeometry_1xPoint_1x2DSize*) pShape)->setSize(Vec2u(10, 15));
				break;
			case GUI_SHAPE_GEOMETRY_2_POINTS: // line
				((CGUIShapeGeometry_2xPoints*) pShape)->setPoint1(vecCursorPosition);
				((CGUIShapeGeometry_2xPoints*) pShape)->setPoint2(vecCursorPosition + Vec2i((int32) 15, 15));
				break;
			case GUI_SHAPE_GEOMETRY_3_POINTS: // triangle
				((CGUIShapeGeometry_3xPoints*) pShape)->setPoint1(vecCursorPosition);
				((CGUIShapeGeometry_3xPoints*) pShape)->setPoint2(vecCursorPosition + Vec2i((int32) 0, 10));
				((CGUIShapeGeometry_3xPoints*) pShape)->setPoint3(vecCursorPosition + Vec2i((int32) 15, 5));
				break;
			case GUI_SHAPE_GEOMETRY_N_POINTS: // polygon
			{
				vector<Vec2i> vecPolygonPoints;
				vecPolygonPoints.resize(5);
				vecPolygonPoints[0] = Vec2i(vecCursorPosition.x, vecCursorPosition.y);
				vecPolygonPoints[1] = Vec2i(vecCursorPosition.x + 15, vecCursorPosition.y + 3);
				vecPolygonPoints[2] = Vec2i(vecCursorPosition.x + 12, vecCursorPosition.y + 10);
				vecPolygonPoints[3] = Vec2i(vecCursorPosition.x + 7, vecCursorPosition.y + 5);
				vecPolygonPoints[4] = Vec2i(vecCursorPosition.x + 4, vecCursorPosition.y + 15);
				((CGUIShapeGeometry_NxPoints*) pShape)->setPoints(vecPolygonPoints);
				break;
			}
			}
			pShape->bindEvents();
		}
		else if (uiAddItemType == 2)
		{
			// control
			eGUIControl eControlId = getActiveControlId();
			CGUIControl *pControl = pLayer->addControl(eControlId, pDefaultItemStyles);
			pControl->setPosition(vecCursorPosition);
			pControl->setSize(getControlDefaultSize(eControlId));

			if (eControlId == GUI_CONTROL_DROP)
			{
				CDropControl *pDrop = (CDropControl*) pControl;
				pDrop->addItem("aaaaa");
				pDrop->addItem("bbbbbbbbbbbbbb");
				pDrop->addItem("c");
			}

			pControl->bindEvents();
		}

		pMainWindow->setMarkedToRedraw(true);
	}
	*/
}

void									CThemeDesignerTab_AddItem::onLeftMouseDown_MainWindow_WindowEventType(Vec2i& vecCursorPosition)
{
	// check to set item active
	CWindow *pMainWindow = bxgx::CGUIManager::get()->getEntryByIndex(1);
	CGUILayer *pLayer = pMainWindow->getEntryByIndex(0);
	CGUIItem *pItem = pLayer->getItemByPoint(vecCursorPosition);
	if (pItem)
	{
		if (pMainWindow->doesActiveItemExist())
		{
			pMainWindow->clearActiveItem();
		}
		pItem->setActiveItem();
		pMainWindow->setMarkedToRedraw(true);
	}
	else
	{
		if (pMainWindow->doesActiveItemExist())
		{
			pMainWindow->clearActiveItem();
			pMainWindow->setMarkedToRedraw(true);
		}
	}

	/*
	todo
	// check to move/resize control
	uint32 uiEdges = CMath::getRectangleResizeEdges(vecCursorPosition, pItem->getBoundingRectanglePosition(), pItem->getBoundingRectangleSize(), 10);
	if (uiEdges == 0)
	{
		// move item
		setMovingItem(pItem);
	}
	else
	{
		// resize item
		setResizingItem(pItem);
	}
	setResizingItemEdges(uiEdges);
	*/
}

// other
uint32									CThemeDesignerTab_AddItem::getTabShapeIndexFromPoint(Vec2i& vecCursorPosition) // todo - rename method? // todo - repeated code f7h8e5t
{
	return CMath::getRowIndexInRectangle(vecCursorPosition, getShapeIconStartPosition() - Vec2i(10, getItemSize().y / 2), getItemSize().x, getItemRowSize().y, 7);
}

uint32									CThemeDesignerTab_AddItem::getTabControlIndexFromPoint(Vec2i& vecCursorPosition) // todo - rename method? // todo - repeated code f7h8e5t
{
	return CMath::getRowIndexInRectangle(vecCursorPosition, getControlIconStartPosition() - Vec2i(10, getItemSize().y / 2), getItemSize().x, getItemRowSize().y, 11);
}

Vec2i								CThemeDesignerTab_AddItem::getShapeRowPoint(uint32 uiShapeRowIndex) // todo - repeated code f7h8e5t
{
	return getShapeIconStartPosition() + Vec2i(-10, ((int32)(uiShapeRowIndex * getItemRowSize().y)) - ((int32) (getItemSize().y / 2))); // todo - 10 repeated 4 times - move to object property
}

Vec2i								CThemeDesignerTab_AddItem::getControlRowPoint(uint32 uiControlRowIndex) // todo - repeated code f7h8e5t
{
	return getControlIconStartPosition() + Vec2i(-10, ((int32) (uiControlRowIndex * getItemRowSize().y)) - ((int32) (getItemSize().y / 2)));
}

eGUIShape								CThemeDesignerTab_AddItem::getShapeIdFromIndex(uint32 uiShapeIndex)
{
	switch (uiShapeIndex)
	{
	case 0:		return GUI_SHAPE_CIRCLE;
	case 1:		return GUI_SHAPE_ELLIPSE;
	case 2:		return GUI_SHAPE_LINE;
	case 3:		return GUI_SHAPE_POLYGON;
	case 4:		return GUI_SHAPE_RECTANGLE;
	case 5:		return GUI_SHAPE_SQUARE;
	case 6:		return GUI_SHAPE_TRIANGLE;
	}
	return GUI_SHAPE_UNKNOWN;
}

eGUIControl								CThemeDesignerTab_AddItem::getControlIdFromIndex(uint32 uiControlIndex)
{
	switch (uiControlIndex)
	{
	case 0:		return GUI_CONTROL_BUTTON;
	case 1:		return GUI_CONTROL_CHECK;
	case 2:		return GUI_CONTROL_DROP;
	case 3:		return GUI_CONTROL_TEXT_BOX;
	case 4:		return GUI_CONTROL_GRID;
	case 5:		return GUI_CONTROL_MENU;
	case 6:		return GUI_CONTROL_PROGRESS;
	case 7:		return GUI_CONTROL_RADIO;
	case 8:		return GUI_CONTROL_SCROLL;
	case 9:		return GUI_CONTROL_TAB_BAR;
	case 10:	return GUI_CONTROL_TEXT;
	}
	return GUI_CONTROL_UNKNOWN;
}

Vec2u							CThemeDesignerTab_AddItem::getControlDefaultSize(eGUIControl eControlId)
{
	switch (eControlId)
	{
	case GUI_CONTROL_BUTTON:	return Vec2u(60, 20);
	case GUI_CONTROL_CHECK:		return Vec2u(20, 20);
	case GUI_CONTROL_DROP:		return Vec2u(80, 25);
	case GUI_CONTROL_TEXT_BOX:	return Vec2u(100, 20);
	case GUI_CONTROL_GRID:		return Vec2u(250, 250);
	case GUI_CONTROL_MENU:		return Vec2u(250, 20);
	case GUI_CONTROL_PROGRESS:	return Vec2u(100, 25);
	case GUI_CONTROL_RADIO:		return Vec2u(20, 20);
	case GUI_CONTROL_SCROLL:	return Vec2u(250, 15);
	case GUI_CONTROL_TAB_BAR:		return Vec2u(250, 25);
	case GUI_CONTROL_TEXT:		return Vec2u(250, 50);
	}
	return Vec2u(50, 50);
}