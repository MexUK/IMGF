#pragma once

#include "nsbxgx.h"
#include "Type/Types.h"
#include "Type/Vector/Vec2i.h"
#include "Pool/VectorPool.h"
#include "Static/Math.h"

class bxgx::Window;

template <class Item>
class bxgx::RectangleItemPlacement
{
public:
	RectangleItemPlacement(void);
	
	void						bindEvents(void);
	void						bindEvents_WhenNotPlacing(void);
	void						bindEvents_WhenPlacing(void);
	
	void						startMovingItem(Item *pItem);
	void						stopMovingItem(void);
	bool						isMovingItem(void) { return m_pItemBeingMoved != nullptr; }
	
	void						startResizingItem(Item *pItem, uint32 uiEdges);
	void						stopResizingItem(void);
	bool						isResizingItem(void) { return m_pItemBeingResized != nullptr; }
	
	void						onLeftMouseDown(bxcf::Vec2i& vecCursorPoint);
	void						onLeftMouseUp(bxcf::Vec2i& vecCursorPoint);
	void						onMouseMove(bxcf::Vec2i& vecCursorPoint);

	void						setItemBeingMoved(Item *pItem) { m_pItemBeingMoved = pItem; }
	Item*						getItemBeingMoved(void) { return m_pItemBeingMoved; }

	void						setItemBeingResized(Item *pItem) { m_pItemBeingResized = pItem; }
	Item*						getItemBeingResized(void) { return m_pItemBeingResized; }
	
	void						setResizingItemEdges(uint32 uiEdges) { m_uiItemResizeEdges = uiEdges; }
	uint32						getResizingItemEdges(void) { return m_uiItemResizeEdges; }

	void						setWindow(Window *pWindow) { m_pWindow = pWindow; }
	Window*					getWindow(void) { return m_pWindow; }

	void						setItems(bxcf::VectorPool<Item*> *pvecItems) { m_pvecItems = pvecItems; }
	bxcf::VectorPool<Item*>*			getItems(void) { return m_pvecItems; }

private:
	void						checkToStartMovingOrResizingItem(bxcf::Vec2i& vecCursorPoint, uint32 uiOuterSpacing);
	
private:
	Item*						m_pItemBeingMoved;		// the item that is being moved or resized
	Item*						m_pItemBeingResized;	// the item that is being moved or resized
	uint8						m_uiItemResizeEdges;
	Window*					m_pWindow;
	bxcf::VectorPool<Item*>*			m_pvecItems;
};

template <class Item>
bxgx::RectangleItemPlacement<Item>::RectangleItemPlacement(void) :
	m_pItemBeingMoved(nullptr),
	m_pItemBeingResized(nullptr),
	m_uiItemResizeEdges(0),
	m_pWindow(0),
	m_pvecItems(nullptr)
{
}

template <class Item>
void					bxgx::RectangleItemPlacement<Item>::bindEvents(void)
{
	//bindEvents_WhenNotPlacing();
}

template <class Item>
void					bxgx::RectangleItemPlacement<Item>::bindEvents_WhenNotPlacing(void)
{
	//markEventUsagess(1, LEFT_MOUSE_DOWN);
}

template <class Item>
void					bxgx::RectangleItemPlacement<Item>::bindEvents_WhenPlacing(void)
{
	//markEventUsagess(2, LEFT_MOUSE_UP, MOVE_MOUSE);
}

template <class Item>
void					bxgx::RectangleItemPlacement<Item>::startMovingItem(Item *pItem)
{
	setItemBeingMoved(pItem);
	bindEvents_WhenPlacing();
}

template <class Item>
void					bxgx::RectangleItemPlacement<Item>::stopMovingItem(void)
{
	unbindEvents();
	setItemBeingMoved(nullptr);
	bindEvents_WhenNotPlacing();
}

template <class Item>
void					bxgx::RectangleItemPlacement<Item>::startResizingItem(Item *pItem, uint32 uiEdges)
{
	setItemBeingResized(pItem);
	setResizingItemEdges(uiEdges);
	bindEvents_WhenPlacing();
}

template <class Item>
void					bxgx::RectangleItemPlacement<Item>::stopResizingItem(void)
{
	unbindEvents();
	setItemBeingResized(nullptr);
	setResizingItemEdges(0);
	bindEvents_WhenNotPlacing();
}

template <class Item>
void					bxgx::RectangleItemPlacement<Item>::checkToStartMovingOrResizingItem(bxcf::Vec2i& vecCursorPoint, uint32 uiOuterSpacing)
{
	uint32 uiRectangleEdges;
	for(Item *pItem : getItems()->getEntries())
	{
		if(pItem->isPointInBoundingRectangle(vecCursorPoint, uiOuterSpacing))
		{
			uiRectangleEdges = bxcf::Math::getRectangleResizeEdges(vecCursorPoint, pItem->getBoundingRectanglePosition(), pItem->getBoundingRectangleSize(), uiOuterSpacing);
			if(uiRectangleEdges == 0)
			{
				// move item
				startMovingItem(pItem);
				break;
			}
			else
			{
				// resize item
				startResizingItem(pItem, uiRectangleEdges);
				break;
			}
		}
	}
}

template <class Item>
void					bxgx::RectangleItemPlacement<Item>::onLeftMouseDown(bxcf::Vec2i& vecCursorPoint)
{
	uint32 uiOuterSpacing = 1;
	checkToStartMovingOrResizingItem(vecCursorPoint, uiOuterSpacing);
}

template <class Item>
void					bxgx::RectangleItemPlacement<Item>::onLeftMouseUp(bxcf::Vec2i& vecCursorPoint)
{
	if (isMovingItem())
	{
		stopMovingItem();
	}
	if (isResizingItem())
	{
		stopResizingItem();
	}
}

template <class Item>
void					bxgx::RectangleItemPlacement<Item>::onMouseMove(bxcf::Vec2i& vecCursorPoint)
{
	if (isMovingItem())
	{
		bxcf::Vec2i
			vecItemPositionChange = bxcf::CEventManager::get()->getScreenCursorMoveDifference();
		getItemBeingMoved()->onMoveItem(vecItemPositionChange);
		getWindow()->render();
	}
	if (isResizingItem())
	{
		bxcf::Vec2i
			vecCursorChange = bxcf::CEventManager::get()->getScreenCursorMoveDifference(),
			vecItemPositionChange,
			vecItemSizeChange;
		bxcf::Math::getResizePositionAndSizeChange(vecCursorChange, getResizingItemEdges(), vecItemPositionChange, vecItemSizeChange);
		getItemBeingResized()->onResizeItem(vecItemPositionChange, vecItemSizeChange);
		getWindow()->render();
	}
}