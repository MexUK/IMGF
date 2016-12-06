#include "CThemeDesignerTab_AddItem.h"
#include "Math/CMath.h"
#include "Event/CEventManager.h"
#include "Event/eEvent.h"
#include "GUI/CGUIManager.h"
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
#include "Type/Vector/CColour.h"
#include "CIMGF.h"
#include "GUI/ThemeDesigner/CThemeDesigner.h"

using namespace std;
using namespace mcore;

auto pOnLeftMouseDown_ThemeDesigner				= [](void *pThemeDesigner, void *pTriggerArg) { ((CThemeDesignerTab_AddItem*) pThemeDesigner)->onLeftMouseDown(*(CPoint2D*) pTriggerArg); };
auto pOnMouseMove_ThemeDesigner					= [](void *pThemeDesigner, void *pTriggerArg) { ((CThemeDesignerTab_AddItem*) pThemeDesigner)->onMouseMove(*(CPoint2D*) pTriggerArg); };
auto pOnLeftMouseDown_ThemeDesigner_MainWindow	= [](void *pThemeDesigner, void *pTriggerArg) { ((CThemeDesignerTab_AddItem*) pThemeDesigner)->onLeftMouseDown_MainWindow(*(CPoint2D*) pTriggerArg); };
auto pOnLeftMouseDown_ThemeDesigner_MainWindow_WindowEventType	= [](void *pThemeDesigner, void *pTriggerArg) { ((CThemeDesignerTab_AddItem*) pThemeDesigner)->onLeftMouseDown_MainWindow_WindowEventType(*(CPoint2D*) pTriggerArg); };

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

	CEventManager *pEventManager = CEventManager::getInstance();
	CWindow *pMainWindow = gui::CGUIManager::getInstance()->getEntryByIndex(1);
	pEventManager->bindEvent(EVENT_TYPE_THEME_DESIGNER, (uint32) pMainWindow->getWindowHandle(), EVENT_onLeftMouseDown, pOnLeftMouseDown_ThemeDesigner_MainWindow, this);

	pMainWindow->bindEvent(EVENT_onLeftMouseDown, pOnLeftMouseDown_ThemeDesigner_MainWindow_WindowEventType, this);
}

// design
void									CThemeDesignerTab_AddItem::initDesign(void)
{
	setShapeIconStartPosition(CPoint2D((int32) 30, 120));
	setShapeTextStartPosition(CPoint2D((int32) 60, 120));
	setControlIconStartPosition(CPoint2D((int32) (250 + 30), 120));
	setControlTextStartPosition(CPoint2D((int32) (250 + 60), 120));
	setItemRowSize(CSize2D(210, 30));
	setItemSize(CSize2D(210, 16));

	CThemeDesigner *pThemeDesigner = getThemeDesigner();

	// add layer
	CGUILayer *pLayer = pThemeDesigner->addLayer("add_item", true);

	// prepare variables
	CGUIShape *pShape = nullptr;
	CGUIControl *pControl = nullptr;

	// fetch window positions and sizes
	CSize2D vecWindowSize = pThemeDesigner->getWindow()->getSize();
	CPoint2D vecWindowCenterPosition = CPoint2D(vecWindowSize.m_x, vecWindowSize.m_y) / 2;
	uint32 uiCenterX = CMath::getCenterX(vecWindowSize.m_x);

	// create styles
	CGUIStyles
		*pStyles_GoldBorder = gui::CGUIManager::createStyles(),
		*pStyles_GoldText = gui::CGUIManager::createStyles(),
		*pStyles_BlueBorder = gui::CGUIManager::createStyles(),
		*pStyles_BlueText = gui::CGUIManager::createStyles(),
		*pStyles_Edit = gui::CGUIManager::createStyles(),
		*pStyles_BlueBorderAndText = gui::CGUIManager::createStyles(),
		*pStyles_Progress = gui::CGUIManager::createStyles(),
		*pStyles_Radio = gui::CGUIManager::createStyles();

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
	pShape = (CGUIShape*) pLayer->addLine(CPoint2D((int32) 0, 80), CPoint2D(vecWindowSize.m_x, 80), pStyles_GoldBorder);					// horizontal line
	pShape = (CGUIShape*) pLayer->addLine(CPoint2D(uiCenterX, 25), CPoint2D(uiCenterX, vecWindowSize.m_y), pStyles_GoldBorder);	// vertical line
	
	// add headers
	pControl = (CGUIControl*) pLayer->addText(CPoint2D((int32) 20, 50), CSize2D(150, 30), "Shapes", pStyles_GoldText);
	pControl = (CGUIControl*) pLayer->addText(CPoint2D(uiCenterX + 20, 50), CSize2D(150, 30), "Controls", pStyles_GoldText);

	// prepare shape icons and text
	uint32
		uiShapeIconX = getShapeIconStartPosition().m_x,
		uiShapeTextX = getShapeTextStartPosition().m_x,
		uiShapeIconY = getShapeIconStartPosition().m_y;

	vector<CPoint2D> vecPolygonPoints;
	vecPolygonPoints.resize(5);
	vecPolygonPoints[0] = CPoint2D(uiShapeIconX, uiShapeIconY + 90);
	vecPolygonPoints[1] = CPoint2D(uiShapeIconX + 15, uiShapeIconY + 90 + 3);
	vecPolygonPoints[2] = CPoint2D(uiShapeIconX + 12, uiShapeIconY + 90 + 10);
	vecPolygonPoints[3] = CPoint2D(uiShapeIconX + 7, uiShapeIconY + 90 + 5);
	vecPolygonPoints[4] = CPoint2D(uiShapeIconX + 4, uiShapeIconY + 90 + 15);

	// add shape icons
	pShape = (CGUIShape*) pLayer->addCircle(				CPoint2D(uiShapeIconX, uiShapeIconY),			7, pStyles_BlueBorder); // todo - make addCircle take a float for radius coz diameter might be odd number
	pShape = (CGUIShape*) pLayer->addEllipse(				CPoint2D(uiShapeIconX + 3, uiShapeIconY + 30),	CSize2D(8, 14), pStyles_BlueBorder);
	pShape = (CGUIShape*) pLayer->addLine(					CPoint2D(uiShapeIconX, uiShapeIconY + 60),		CPoint2D(uiShapeIconX + 15, 120 + 60 + 15), pStyles_BlueBorder);
	pShape = (CGUIShape*) pLayer->addPolygon(vecPolygonPoints, pStyles_BlueBorder);
	pShape = (CGUIShape*) pLayer->addRectangle(				CPoint2D(uiShapeIconX + 3, uiShapeIconY + 120),	CSize2D(8, 15), pStyles_BlueBorder);
	pShape = (CGUIShape*) pLayer->addSquare(				CPoint2D(uiShapeIconX, uiShapeIconY + 150),		15, pStyles_BlueBorder);
	pShape = (CGUIShape*) pLayer->addEquilateralTriangle(	CPoint2D(uiShapeIconX, uiShapeIconY + 195),		15.0f, 0.0f, pStyles_BlueBorder);

	// add shape text
	pControl = (CGUIControl*) pLayer->addText(CPoint2D(uiShapeTextX, uiShapeIconY), CSize2D(150, 30), "Circle", pStyles_BlueText);
	pControl = (CGUIControl*) pLayer->addText(CPoint2D(uiShapeTextX, uiShapeIconY + 30), CSize2D(150, 30), "Ellipse", pStyles_BlueText);
	pControl = (CGUIControl*) pLayer->addText(CPoint2D(uiShapeTextX, uiShapeIconY + 60), CSize2D(150, 30), "Line", pStyles_BlueText);
	pControl = (CGUIControl*) pLayer->addText(CPoint2D(uiShapeTextX, uiShapeIconY + 90), CSize2D(150, 30), "Polygon", pStyles_BlueText);
	pControl = (CGUIControl*) pLayer->addText(CPoint2D(uiShapeTextX, uiShapeIconY + 120), CSize2D(150, 30), "Rectangle", pStyles_BlueText);
	pControl = (CGUIControl*) pLayer->addText(CPoint2D(uiShapeTextX, uiShapeIconY + 150), CSize2D(150, 30), "Square", pStyles_BlueText);
	pControl = (CGUIControl*) pLayer->addText(CPoint2D(uiShapeTextX, uiShapeIconY + 180), CSize2D(150, 30), "Triangle", pStyles_BlueText);

	// prepare control icons and text
	uint32
		uiControlIconX = uiCenterX + 30,
		uiControlTextX = uiCenterX + 60,
		uiControlIconY = 120;

	// add control icons
	pControl = (CGUIControl*) pLayer->addButton(CPoint2D(uiControlIconX, uiControlIconY), CSize2D(15, 9), "", pStyles_BlueBorder);

	pControl = (CGUIControl*) pLayer->addCheck(CPoint2D(uiControlIconX, uiControlIconY + 30), CSize2D(15, 15), "", pStyles_BlueBorder);
	((CCheckControl*) pControl)->setMarked(true);

	pControl = (CGUIControl*) pLayer->addDrop(CPoint2D(uiControlIconX, uiControlIconY + 60), CSize2D(15, 10), pStyles_BlueBorder);

	pControl = (CGUIControl*) pLayer->addEdit(CPoint2D(uiControlIconX, uiControlIconY + 90), CSize2D(15, 15), "", true, pStyles_Edit);
	pControl = (CGUIControl*) pLayer->addList(CPoint2D(uiControlIconX, uiControlIconY + 120), CSize2D(15, 15), pStyles_BlueBorder);
	// todo pControl = (CGUIControl*) pLayer->addMenu(CPoint2D(uiControlIconX, uiControlIconY + 150), CSize2D(15, 15), pStyles_BlueBorder);

	pControl = (CGUIControl*) pLayer->addProgress(CPoint2D(uiControlIconX, uiControlIconY + 180), CSize2D(15, 12), pStyles_Progress);
	((CProgressControl*) pControl)->setProgress(0.7);
	((CProgressControl*) pControl)->setCompletionPercentageShown(false);

	pControl = (CGUIControl*) pLayer->addRadio(CPoint2D(uiControlIconX, uiControlIconY + 210), CSize2D(15, 15), "", pStyles_Radio);
	((CRadioControl*) pControl)->setMarked(true);

	pControl = (CGUIControl*) pLayer->addScroll(CPoint2D(uiControlIconX, uiControlIconY + 240), CSize2D(10, 15), pStyles_BlueBorder);
	// todo pControl = (CGUIControl*) pLayer->addTabs(CPoint2D(uiControlIconX, uiControlIconY + 270), CSize2D(15, 15), "Tabs", pStyles_BlueBorder);
	pControl = (CGUIControl*) pLayer->addText(CPoint2D(uiControlIconX, uiControlIconY + 300), CSize2D(15, 15), "abc", pStyles_BlueBorderAndText);

	// add control text
	pControl = (CGUIControl*) pLayer->addText(CPoint2D(uiControlTextX, uiControlIconY), CSize2D(150, 30), "Button", pStyles_BlueText);
	pControl = (CGUIControl*) pLayer->addText(CPoint2D(uiControlTextX, uiControlIconY + 30), CSize2D(150, 30), "Check", pStyles_BlueText);
	pControl = (CGUIControl*) pLayer->addText(CPoint2D(uiControlTextX, uiControlIconY + 60), CSize2D(150, 30), "Drop", pStyles_BlueText);
	pControl = (CGUIControl*) pLayer->addText(CPoint2D(uiControlTextX, uiControlIconY + 90), CSize2D(150, 30), "Edit", pStyles_BlueText);
	pControl = (CGUIControl*) pLayer->addText(CPoint2D(uiControlTextX, uiControlIconY + 120), CSize2D(150, 30), "List", pStyles_BlueText);
	pControl = (CGUIControl*) pLayer->addText(CPoint2D(uiControlTextX, uiControlIconY + 150), CSize2D(150, 30), "Menu", pStyles_BlueText);
	pControl = (CGUIControl*) pLayer->addText(CPoint2D(uiControlTextX, uiControlIconY + 180), CSize2D(150, 30), "Progress", pStyles_BlueText);
	pControl = (CGUIControl*) pLayer->addText(CPoint2D(uiControlTextX, uiControlIconY + 210), CSize2D(150, 30), "Radio", pStyles_BlueText);
	pControl = (CGUIControl*) pLayer->addText(CPoint2D(uiControlTextX, uiControlIconY + 240), CSize2D(150, 30), "Scroll", pStyles_BlueText);
	pControl = (CGUIControl*) pLayer->addText(CPoint2D(uiControlTextX, uiControlIconY + 270), CSize2D(150, 30), "Tabs", pStyles_BlueText);
	pControl = (CGUIControl*) pLayer->addText(CPoint2D(uiControlTextX, uiControlIconY + 300), CSize2D(150, 30), "Text", pStyles_BlueText);
}

// input - theme designer window
void									CThemeDesignerTab_AddItem::onLeftMouseDown(CPoint2D& vecCursorPosition)
{
	getIMGF()->getThemeDesigner()->setThemeDesignerModeEnabled(true);
	gui::CGUIManager::getInstance()->getEntryByIndex(1)->setMarkedToRedraw(true); // redraw main window title bar

	uint32
		uiShapeIndex,
		uiControlIndex;
	CPoint2D
		vecRectanglePosition;
	CSize2D
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
			getThemeDesigner()->getActiveItemRectangle()->getLayer()->getShapes().removeEntry(getThemeDesigner()->getActiveItemRectangle());
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
			getThemeDesigner()->getActiveItemRectangle()->getLayer()->getShapes().removeEntry(getThemeDesigner()->getActiveItemRectangle());
			getThemeDesigner()->setActiveItemRectangle(nullptr);
			getThemeDesigner()->getWindow()->setMarkedToRedraw(true);
		}

		getIMGF()->getThemeDesigner()->setThemeDesignerModeEnabled(false);
	}
}

void									CThemeDesignerTab_AddItem::onMouseMove(CPoint2D& vecCursorPosition)
{
	uint32
		uiShapeIndex,
		uiControlIndex;
	CPoint2D
		vecRectanglePosition;
	CSize2D
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
			getThemeDesigner()->getItemHoverRectangle()->getLayer()->getShapes().removeEntry(getThemeDesigner()->getItemHoverRectangle());
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
			getThemeDesigner()->getItemHoverRectangle()->getLayer()->getShapes().removeEntry(getThemeDesigner()->getItemHoverRectangle());
			getThemeDesigner()->setItemHoverRectangle(nullptr);
			getThemeDesigner()->getWindow()->setMarkedToRedraw(true);
		}
	}
}

// input - main window
void									CThemeDesignerTab_AddItem::onLeftMouseDown_MainWindow(CPoint2D& vecCursorPosition)
{
	CWindow *pMainWindow = gui::CGUIManager::getInstance()->getEntryByIndex(1);

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
				((CGUIShapeGeometry_1xPoint_1x2DSize*) pShape)->setSize(CSize2D(10, 15));
				break;
			case GUI_SHAPE_GEOMETRY_2_POINTS: // line
				((CGUIShapeGeometry_2xPoints*) pShape)->setPoint1(vecCursorPosition);
				((CGUIShapeGeometry_2xPoints*) pShape)->setPoint2(vecCursorPosition + CPoint2D((int32) 15, 15));
				break;
			case GUI_SHAPE_GEOMETRY_3_POINTS: // triangle
				((CGUIShapeGeometry_3xPoints*) pShape)->setPoint1(vecCursorPosition);
				((CGUIShapeGeometry_3xPoints*) pShape)->setPoint2(vecCursorPosition + CPoint2D((int32) 0, 10));
				((CGUIShapeGeometry_3xPoints*) pShape)->setPoint3(vecCursorPosition + CPoint2D((int32) 15, 5));
				break;
			case GUI_SHAPE_GEOMETRY_N_POINTS: // polygon
			{
				vector<CPoint2D> vecPolygonPoints;
				vecPolygonPoints.resize(5);
				vecPolygonPoints[0] = CPoint2D(vecCursorPosition.m_x, vecCursorPosition.m_y);
				vecPolygonPoints[1] = CPoint2D(vecCursorPosition.m_x + 15, vecCursorPosition.m_y + 3);
				vecPolygonPoints[2] = CPoint2D(vecCursorPosition.m_x + 12, vecCursorPosition.m_y + 10);
				vecPolygonPoints[3] = CPoint2D(vecCursorPosition.m_x + 7, vecCursorPosition.m_y + 5);
				vecPolygonPoints[4] = CPoint2D(vecCursorPosition.m_x + 4, vecCursorPosition.m_y + 15);
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
}

void									CThemeDesignerTab_AddItem::onLeftMouseDown_MainWindow_WindowEventType(CPoint2D& vecCursorPosition)
{
	// check to set item active
	CWindow *pMainWindow = gui::CGUIManager::getInstance()->getEntryByIndex(1);
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
uint32									CThemeDesignerTab_AddItem::getTabShapeIndexFromPoint(CPoint2D& vecCursorPosition) // todo - rename method? // todo - repeated code f7h8e5t
{
	return CMath::getRowIndexInRectangle(vecCursorPosition, getShapeIconStartPosition() - CPoint2D(10, getItemSize().m_y / 2), getItemSize().m_x, getItemRowSize().m_y, 7);
}

uint32									CThemeDesignerTab_AddItem::getTabControlIndexFromPoint(CPoint2D& vecCursorPosition) // todo - rename method? // todo - repeated code f7h8e5t
{
	return CMath::getRowIndexInRectangle(vecCursorPosition, getControlIconStartPosition() - CPoint2D(10, getItemSize().m_y / 2), getItemSize().m_x, getItemRowSize().m_y, 11);
}

CPoint2D								CThemeDesignerTab_AddItem::getShapeRowPoint(uint32 uiShapeRowIndex) // todo - repeated code f7h8e5t
{
	return getShapeIconStartPosition() + CPoint2D(-10, ((int32)(uiShapeRowIndex * getItemRowSize().m_y)) - ((int32) (getItemSize().m_y / 2))); // todo - 10 repeated 4 times - move to object property
}

CPoint2D								CThemeDesignerTab_AddItem::getControlRowPoint(uint32 uiControlRowIndex) // todo - repeated code f7h8e5t
{
	return getControlIconStartPosition() + CPoint2D(-10, ((int32) (uiControlRowIndex * getItemRowSize().m_y)) - ((int32) (getItemSize().m_y / 2)));
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
	case 3:		return GUI_CONTROL_EDIT;
	case 4:		return GUI_CONTROL_LIST;
	case 5:		return GUI_CONTROL_MENU;
	case 6:		return GUI_CONTROL_PROGRESS;
	case 7:		return GUI_CONTROL_RADIO;
	case 8:		return GUI_CONTROL_SCROLL;
	case 9:		return GUI_CONTROL_TAB;
	case 10:	return GUI_CONTROL_TEXT;
	}
	return GUI_CONTROL_UNKNOWN;
}

CSize2D							CThemeDesignerTab_AddItem::getControlDefaultSize(eGUIControl eControlId)
{
	switch (eControlId)
	{
	case GUI_CONTROL_BUTTON:	return CSize2D(60, 20);
	case GUI_CONTROL_CHECK:		return CSize2D(20, 20);
	case GUI_CONTROL_DROP:		return CSize2D(80, 25);
	case GUI_CONTROL_EDIT:		return CSize2D(100, 20);
	case GUI_CONTROL_LIST:		return CSize2D(250, 250);
	case GUI_CONTROL_MENU:		return CSize2D(250, 20);
	case GUI_CONTROL_PROGRESS:	return CSize2D(100, 25);
	case GUI_CONTROL_RADIO:		return CSize2D(20, 20);
	case GUI_CONTROL_SCROLL:	return CSize2D(250, 15);
	case GUI_CONTROL_TAB:		return CSize2D(250, 25);
	case GUI_CONTROL_TEXT:		return CSize2D(250, 50);
	}
	return CSize2D(50, 50);
}