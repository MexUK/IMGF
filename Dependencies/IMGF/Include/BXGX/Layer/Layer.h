#pragma once

#include "nsbxgx.h"
#include "Type/Types.h"
#include "Pool/VectorPool.h"
#include "Shape/Base/Shape.h"
#include "Control/Base/Control.h"
#include "Control/Base/EControl.h"
#include "Type/Vector/Vec2i.h"
#include "Type/Vector/Vec2u.h"
#include "Item/Render/RenderItem.h"
#include "Item/Render/ERenderItem.h"
#include "Layer/ELayerType.h"
#include <string>
#include <vector>

class bxgx::Circle;
class bxgx::Ellipse;
class bxgx::Line;
class bxgx::Polygon;
class bxgx::Rectangle;
class bxgx::Square;
class bxgx::Triangle;

class bxgx::Button;
class bxgx::CheckBox;
class bxgx::DropDown;
class bxgx::TextBox;
class bxgx::Image;
class bxgx::Grid;
class bxgx::Menu;
class bxgx::ProgressBar;
class bxgx::RadioButton;
class bxgx::ScrollBar;
class bxgx::TabBar;
class bxgx::Text;

class bxgx::LayerItem;

class bxgx::Layer : public RenderItem
{
public:
	Layer(void);

	void					unload(void) {}

	void					bindEvents(void);
	void					unbindEvents(void);

	void					bindItemEvents(void);
	void					unbindItemEvents(void);

	void					unserialize(void);
	void					serialize(void);

	bxgx::item::ERenderItem	getItemType(void) { return bxgx::item::LAYER; }
	uint32					getItemSubType(void) { return bxgx::item::layer::TYPE_1; }

	bool					isPointInItem(bxcf::Vec2i& vecPoint);
	bool					doesItemHaveFocus(void) { return true; }

	void					setWindow(Window *pWindow) { m_pWindow = pWindow; }
	Window*					getWindow(void) { return m_pWindow; }

	void					setEnabled(bool bEnabled);
	void					setEnabledWithoutEvents(bool bEnabled) { m_bEnabled = bEnabled; }
	bool					isEnabled(void) { return m_bEnabled; }

	void					setId(uint32 uiId) { m_uiId = uiId; }
	uint32					getId(void) { return m_uiId; }

	void					setZIndex(int32 iZIndex) { m_iZIndex = iZIndex; }
	int32					getZIndex(void) { return m_iZIndex; }

	LayerItem*				getItemByPoint(bxcf::Vec2i& vecPoint, bxgx::EControl eControlType = UNKNOWN_CONTROL);

	// controls
	bxgx::Control*			addControl(bxgx::EControl eControlId, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	void					removeControl(bxgx::Control *pControl);
	void					removeAllControls(void);

	Button*					addButton(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize, std::string strButtonText, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	CheckBox*				addCheck(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize, std::string strCheckText, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	DropDown*				addDrop(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize, std::string strDefaultText, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	Image*					addImage(bxcf::Vec2i& vecPosition, std::string strImagePath, bxcf::Vec2u vecSize = bxcf::Vec2u(0, 0), std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	// todo Image*			addImageMem(bxcf::Vec2i& vecPosition, std::string& strImageData, bxcf::Vec2u vecSize = bxcf::Vec2u(0, 0), std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	Grid*					addGrid(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	Menu*					addMenu(bxcf::Vec2i& vecPosition, uint32 uiMenuLength, uint32 uiMenuItemLength, bxcf::E2DAxis uiOrientation, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	ProgressBar*			addProgress(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	RadioButton*			addRadio(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize, std::string strRadioText, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	ScrollBar*				addScroll(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	TabBar*					addTabBar(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	Text*					addText(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize, std::string strText, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	TextBox*				addTextBox(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize, std::string strText = "", bool bMultiLine = false, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);

	Button*					addButton(int32 x, int32 y, int32 w, int32 h, std::string strButtonText, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	CheckBox*				addCheck(int32 x, int32 y, int32 w, int32 h, std::string strCheckText, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	DropDown*				addDrop(int32 x, int32 y, int32 w, int32 h, std::string strDefaultText, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	Image*					addImage(int32 x, int32 y, std::string strImagePath, int32 w = 0, int32 h = 0, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	Grid*					addGrid(int32 x, int32 y, int32 w, int32 h, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	Menu*					addMenu(int32 x, int32 y, uint32 uiMenuLength, uint32 uiMenuItemLength, bxcf::E2DAxis uiOrientation, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	ProgressBar*			addProgress(int32 x, int32 y, int32 w, int32 h, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	RadioButton*			addRadio(int32 x, int32 y, int32 w, int32 h, std::string strRadioText, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	ScrollBar*				addScroll(int32 x, int32 y, int32 w, int32 h, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	TabBar*					addTabBar(int32 x, int32 y, int32 w, int32 h, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	Text*					addText(int32 x, int32 y, int32 w, int32 h, std::string strText, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	TextBox*				addTextBox(int32 x, int32 y, int32 w, int32 h, std::string strText = "", bool bMultiLine = false, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);

	// shapes
	Shape*					addShape(EShape eShapeId, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	void					removeShape(Shape *pShape);
	void					removeAllShapes(void);

	Line*					addLine(bxcf::Vec2i& vecPoint1, bxcf::Vec2i& vecPoint2, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	Square*					addSquare(bxcf::Vec2i& vecPosition, uint32 uiSideLength, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	Rectangle*				addRectangle(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	Circle*					addCircle(bxcf::Vec2i& vecPosition, uint32 uiRadius, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);		// position is top left of circle
	Ellipse*				addEllipse(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	Polygon*				addPolygon(std::vector<bxcf::Vec2i>& vecPoints, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);

	Line*					addLine(int32 x1, int32 y1, int32 x2, int32 y2, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	Square*					addSquare(int32 x, int32 y, int32 w, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	Rectangle*				addRectangle(int32 x, int32 y, int32 w, int32 h, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	Circle*					addCircle(int32 x, int32 y, int32 r, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);		// position is top left of circle
	Ellipse*				addEllipse(int32 x, int32 y, int32 rw, int32 rh, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	
	Triangle*				addTriangle(bxcf::Vec2i& vecPoint1, bxcf::Vec2i& vecPoint2, bxcf::Vec2i& vecPoint3, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);		// scalene or any triangle type
	Triangle*				addEquilateralTriangle(bxcf::Vec2i& vecPosition, float32 fSideLength, uint32 uiPointingDirection, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0); // [parameter uiPointingDirection] Left=1,Top=2,Right=3,Bottom=4,TopLeft=5,TopRight=6,BottomRight=7,BottomLeft=8
	Triangle*				addEquilateralTriangle(bxcf::Vec2i& vecBottomLeftPoint, bxcf::Vec2i& vecBottomRightPoint, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	Triangle*				addEquilateralTriangle(bxcf::Vec2i& vecBottomLeftPoint, float32 fSideLength, float32 fBaseAngle = 0.0f, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);	// base angle parameter is in degrees
	Triangle*				addIsoscelesTriangle(bxcf::Vec2i& vecPosition, float32 fBaseLength, float32 fLegLength, uint32 uiPointingDirection, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0); // [parameter uiPointingDirection] Left=1,Top=2,Right=3,Bottom=4,TopLeft=5,TopRight=6,BottomRight=7,BottomLeft=8
	Triangle*				addIsoscelesTriangle(bxcf::Vec2i& vecBaseCenterPoint, bxcf::Vec2i& vecTipPoint, uint32 uiBaseHalfWidth, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);
	Triangle*				addIsoscelesTriangle(bxcf::Vec2i& vecBottomLeftPoint, float32 fBaseLength, float32 fTipAngle = 25.0f, float32 fBaseAngle = 0.0f, std::string strStyleGroups = "", uint32 uiItemId = -1, int32 iZIndex = 0);	// tip angle parameter is in degrees

	// Layer continued.
	bxcf::VectorPool<Shape*>*			getShapes(void) { return m_pShapes; }
	bxcf::VectorPool<bxgx::Control*>*	getControls(void) { return m_pControls; }

	bxgx::LayerItem*		getItemById(uint32 uiItemId);

	void					render(void);

private:
	void					initializeControl(bxgx::Control *pWindowControl, bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize, std::string& strStyleGroups, uint32 uiItemId, int32 iZIndex = 0);
	void					initializeControl(bxgx::Control *pWindowControl, std::string& strStyleGroups, uint32 uiItemId, int32 iZIndex = 0);
	void					initializeShape(Shape *pShape, std::string& strStyleGroups, uint32 uiItemId, int32 iZIndex = 0);

	uint32					getControlInsertionIndex(int32 iZIndex);
	uint32					getShapeInsertionIndex(int32 iZIndex);

	Shape*					createShapeFromId(EShape eShapeId);
	bxgx::Control*			createControlFromId(bxgx::EControl eControlId);

protected:
	Window*								m_pWindow;

private:
	bool								m_bEnabled;
	uint32								m_uiId;
	int32								m_iZIndex;
	bxcf::VectorPool<Shape*>*			m_pShapes;
	bxcf::VectorPool<bxgx::Control*>*	m_pControls;
};