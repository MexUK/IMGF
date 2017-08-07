#ifndef CRectangleItemPlacement_H
#define CRectangleItemPlacement_H

#include "Type/Types.h"
#include "Type/Vector/CPoint2D.h"
#include "Type/Vector/CSize2D.h"
#include "Pool/CVectorPool.h"
#include "Event/eEvent.h"
#include "Event/CEventManager.h"
#include "Event/CEventBinder.h"
#include "Event/CInputEventCallbacks.h"
#include "Math/CMath.h"
#include <vector>

class CWindow;

template <class Item>
class CRectangleItemPlacement : public bxcf::CEventBinder, public bxcf::CInputEventCallbacks
{
public:
	CRectangleItemPlacement(void);
	
	void						bindEvents(void);
	void						bindEvents_WhenNotPlacing(void);
	void						bindEvents_WhenPlacing(void);
	
	void						startMovingItem(Item *pItem);
	void						stopMovingItem(void);
	bool						isMovingItem(void) { return m_pItemBeingMoved != nullptr; }
	
	void						startResizingItem(Item *pItem, uint32 uiEdges);
	void						stopResizingItem(void);
	bool						isResizingItem(void) { return m_pItemBeingResized != nullptr; }
	
	void						onLeftMouseDown(bxcf::CPoint2D& vecCursorPoint);
	void						onLeftMouseUp(bxcf::CPoint2D& vecCursorPoint);
	void						onMouseMove(bxcf::CPoint2D& vecCursorPoint);

	void						setItemBeingMoved(Item *pItem) { m_pItemBeingMoved = pItem; }
	Item*						getItemBeingMoved(void) { return m_pItemBeingMoved; }

	void						setItemBeingResized(Item *pItem) { m_pItemBeingResized = pItem; }
	Item*						getItemBeingResized(void) { return m_pItemBeingResized; }
	
	void						setResizingItemEdges(uint32 uiEdges) { m_uiItemResizeEdges = uiEdges; }
	uint32						getResizingItemEdges(void) { return m_uiItemResizeEdges; }

	void						setWindow(CWindow *pWindow) { m_pWindow = pWindow; }
	CWindow*					getWindow(void) { return m_pWindow; }

	void						setItems(bxcf::CVectorPool<Item*> *pvecItems) { m_pvecItems = pvecItems; }
	bxcf::CVectorPool<Item*>*			getItems(void) { return m_pvecItems; }

private:
	void						checkToStartMovingOrResizingItem(bxcf::CPoint2D& vecCursorPoint, uint32 uiOuterSpacing);
	
private:
	Item*						m_pItemBeingMoved;		// the item that is being moved or resized
	Item*						m_pItemBeingResized;	// the item that is being moved or resized
	uint8						m_uiItemResizeEdges;
	CWindow*					m_pWindow;
	bxcf::CVectorPool<Item*>*			m_pvecItems;
};

template <class Item>
CRectangleItemPlacement<Item>::CRectangleItemPlacement(void) :
	m_pItemBeingMoved(nullptr),
	m_pItemBeingResized(nullptr),
	m_uiItemResizeEdges(0),
	m_pWindow(0),
	m_pvecItems(nullptr)
{
}

template <class Item>
void					CRectangleItemPlacement<Item>::bindEvents(void)
{
	bindEvents_WhenNotPlacing();
}

template <class Item>
void					CRectangleItemPlacement<Item>::bindEvents_WhenNotPlacing(void)
{
	storeEventBoundFunction(getWindow()->bindEvent(bxcf::EVENT_onLeftMouseDown, this, nullptr, -10));
}

template <class Item>
void					CRectangleItemPlacement<Item>::bindEvents_WhenPlacing(void)
{
	storeEventBoundFunction(getWindow()->bindEvent(bxcf::EVENT_onLeftMouseUp, this));
	storeEventBoundFunction(getWindow()->bindEvent(bxcf::EVENT_onMouseMove, this));
}

template <class Item>
void					CRectangleItemPlacement<Item>::startMovingItem(Item *pItem)
{
	setItemBeingMoved(pItem);
	bindEvents_WhenPlacing();
}

template <class Item>
void					CRectangleItemPlacement<Item>::stopMovingItem(void)
{
	unbindEvents();
	setItemBeingMoved(nullptr);
	bindEvents_WhenNotPlacing();
}

template <class Item>
void					CRectangleItemPlacement<Item>::startResizingItem(Item *pItem, uint32 uiEdges)
{
	setItemBeingResized(pItem);
	setResizingItemEdges(uiEdges);
	bindEvents_WhenPlacing();
}

template <class Item>
void					CRectangleItemPlacement<Item>::stopResizingItem(void)
{
	unbindEvents();
	setItemBeingResized(nullptr);
	setResizingItemEdges(0);
	bindEvents_WhenNotPlacing();
}

template <class Item>
void					CRectangleItemPlacement<Item>::checkToStartMovingOrResizingItem(bxcf::CPoint2D& vecCursorPoint, uint32 uiOuterSpacing)
{
	uint32 uiRectangleEdges;
	for(Item *pItem : getItems()->getEntries())
	{
		if(pItem->isPointInBoundingRectangle(vecCursorPoint, uiOuterSpacing))
		{
			uiRectangleEdges = bxcf::CMath::getRectangleResizeEdges(vecCursorPoint, pItem->getBoundingRectanglePosition(), pItem->getBoundingRectangleSize(), uiOuterSpacing);
			if(uiRectangleEdges == 0)
			{
				// move item
				startMovingItem(pItem);
				bxcf::CEventManager::get()->setEventHogged(true);
				break;
			}
			else
			{
				// resize item
				startResizingItem(pItem, uiRectangleEdges);
				bxcf::CEventManager::get()->setEventHogged(true);
				break;
			}
		}
	}
}

template <class Item>
void					CRectangleItemPlacement<Item>::onLeftMouseDown(bxcf::CPoint2D& vecCursorPoint)
{
	uint32 uiOuterSpacing = 1;
	checkToStartMovingOrResizingItem(vecCursorPoint, uiOuterSpacing);
}

template <class Item>
void					CRectangleItemPlacement<Item>::onLeftMouseUp(bxcf::CPoint2D& vecCursorPoint)
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
void					CRectangleItemPlacement<Item>::onMouseMove(bxcf::CPoint2D& vecCursorPoint)
{
	if (isMovingItem())
	{
		bxcf::CVector2i32
			vecItemPositionChange = bxcf::CEventManager::get()->getScreenCursorMoveDifference();
		getItemBeingMoved()->onMoveItem(vecItemPositionChange);
		getWindow()->setMarkedToRedraw(true);
	}
	if (isResizingItem())
	{
		bxcf::CVector2i32
			vecCursorChange = bxcf::CEventManager::get()->getScreenCursorMoveDifference(),
			vecItemPositionChange,
			vecItemSizeChange;
		bxcf::CMath::getResizePositionAndSizeChange(vecCursorChange, getResizingItemEdges(), vecItemPositionChange, vecItemSizeChange);
		getItemBeingResized()->onResizeItem(vecItemPositionChange, vecItemSizeChange);
		getWindow()->setMarkedToRedraw(true);
	}
}

#endif