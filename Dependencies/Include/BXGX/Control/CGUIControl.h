#ifndef CGUIControl_H
#define CGUIControl_H

#include "Type/Types.h"
#include "Type/Vector/Vec2i.h"
#include "Type/Vector/Vec2u.h"
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

class CGUIControl : public CGUIItem, public bxcf::CEventType
{
public:
	CGUIControl(eGUIControl eControlType);
	virtual ~CGUIControl(void);

	void									unload(void) {}

	virtual void							unserialize(bool bSkipControlId = false);
	virtual void							serialize(void);

	bxcf::CEventBoundFunction*				bindEvent(uint32 uiEventId, void(*pFunction)(void*), void *pTriggerArgument = nullptr, int32 iZOrder = 0);
	bxcf::CEventBoundFunction*				bindEvent(uint32 uiEventId, void(*pFunction)(void*, void*), void *pTriggerArgument = nullptr, int32 iZOrder = 0);
	bxcf::CEventBoundFunction*				bindEvent(uint32 uiEventId, bxcf::CInputEventCallbacks *pObject, void *pTriggerArgument = nullptr, int32 iZOrder = 0);
	bool									triggerEvent(uint32 uiEventId, void *pTriggerArgument = nullptr);

	uint32									getItemType(void) { return bxgx::item::CONTROL; }
	uint32									getItemSubType(void) { return m_eControlType; }

	virtual bool							isPointInItem(bxcf::Vec2i& vecPoint);

	virtual bxcf::Vec2i						getBoundingRectanglePosition(void) { return m_vecPosition; }
	virtual bxcf::Vec2u						getBoundingRectangleSize(void) { return m_vecSize; }
	void									moveItem(bxcf::Vec2i& vecPositionChange) { m_vecPosition += vecPositionChange; }
	void									resizeItemViaOffsets(bxcf::Vec2i& vecItemSizeChange) { m_vecSize += bxcf::Vec2u(vecItemSizeChange.x, vecItemSizeChange.y); }

	void									addScroll(CScrollControl *pScroll);

	void									setControlType(eGUIControl eControlType) { m_eControlType = eControlType; }
	eGUIControl								getControlType(void) { return m_eControlType; }
	
	void									setControlId(uint32 uiControlId) { m_uiControlId = uiControlId; }
	uint32									getControlId(void) { return m_uiControlId; }
	
	void									setPosition(bxcf::Vec2i& vecPosition) { m_vecPosition = vecPosition; }
	bxcf::Vec2i&							getPosition(void) { return m_vecPosition; }
	
	void									setSize(bxcf::Vec2u& vecSize) { m_vecSize = vecSize; }
	bxcf::Vec2u&							getSize(void) { return m_vecSize; }
	
	void									setPointMarkedAsInControl(bool bPointMarkedAsInControl) { m_bPointMarkedAsInControl = bPointMarkedAsInControl; }
	bool									isPointMarkedAsInControl(void) { return m_bPointMarkedAsInControl; }

	CGUIScrollPool*							getScrolls(void) { return m_pScrolls; }

	bool									doesHaveHoverIcon(void);

private:
	eGUIControl								m_eControlType;
	bxcf::Vec2i								m_vecPosition;
	bxcf::Vec2u								m_vecSize;
	uint32									m_uiControlId;
	uint8									m_bPointMarkedAsInControl		: 1;
	CGUIScrollPool*							m_pScrolls;
};

#endif