#ifndef CGUIControl_H
#define CGUIControl_H

#include "Type/Types.h"
#include "Type/Vector/CPoint2D.h"
#include "Type/Vector/CSize2D.h"
#include "eGUIControl.h"
#include "Pool/CVectorPool.h"
#include "Event/CEventBoundFunction.h"
#include "Event/CEventType.h"
#include "Event/CEventBinder.h"
#include "Item/CGUIItem.h"
#include <string>
#include <vector>
#include <Windows.h>
#include <gdiplus.h>

class CWindow;
class CGUIScrollPool;
class CGUILayer;
class CGUIStyles;
class CScrollControl;

class CGUIControl : public CGUIItem, public mcore::CEventType
{
public:
	CGUIControl(eGUIControl eControlType);
	~CGUIControl(void);

	void									unload(void) {}

	virtual void							unserialize(bool bSkipControlId = false);
	virtual void							serialize(void);

	mcore::CEventBoundFunction*				bindEvent(uint32 uiEventId, void(*pFunction)(void*), void *pTriggerArgument = nullptr, int32 iZOrder = 0);
	mcore::CEventBoundFunction*				bindEvent(uint32 uiEventId, void(*pFunction)(void*, void*), void *pTriggerArgument = nullptr, int32 iZOrder = 0);
	mcore::CEventBoundFunction*				bindEvent(uint32 uiEventId, mcore::CInputEventCallbacks *pObject, void *pTriggerArgument = nullptr, int32 iZOrder = 0);
	bool									triggerEvent(uint32 uiEventId, void *pTriggerArgument = nullptr);

	virtual bool							isPointInItem(mcore::CPoint2D& vecPoint);
	mcore::CPoint2D								getBoundingRectanglePosition(void) { return m_vecPosition; }
	mcore::CSize2D									getBoundingRectangleSize(void) { return m_vecSize; }
	void									moveItem(mcore::CVector2i32& vecPositionChange) { m_vecPosition += vecPositionChange; }
	void									resizeItemViaOffsets(mcore::CVector2i32& vecItemSizeChange) { m_vecSize += mcore::CSize2D(vecItemSizeChange.m_x, vecItemSizeChange.m_y); }

	bool									doesControlHaveFocus(void);

	void									addScroll(CScrollControl *pScroll);

	void									setControlType(eGUIControl eControlType) { m_eControlType = eControlType; }
	eGUIControl								getControlType(void) { return m_eControlType; }
	
	void									setControlId(uint32 uiControlId) { m_uiControlId = uiControlId; }
	uint32									getControlId(void) { return m_uiControlId; }
	
	void									setPosition(mcore::CPoint2D& vecPosition) { m_vecPosition = vecPosition; }
	mcore::CPoint2D&								getPosition(void) { return m_vecPosition; }
	
	void									setSize(mcore::CSize2D& vecSize) { m_vecSize = vecSize; }
	mcore::CSize2D&								getSize(void) { return m_vecSize; }
	
	void									setPointMarkedAsInControl(bool bPointMarkedAsInControl) { m_bPointMarkedAsInControl = bPointMarkedAsInControl; }
	bool									isPointMarkedAsInControl(void) { return m_bPointMarkedAsInControl; }

	CGUIScrollPool*							getScrolls(void) { return m_pScrolls; }

private:
	eGUIControl								m_eControlType;
	mcore::CPoint2D								m_vecPosition;
	mcore::CSize2D									m_vecSize;
	uint32									m_uiControlId;
	uint8									m_bPointMarkedAsInControl		: 1;
	CGUIScrollPool*							m_pScrolls;
};

#endif