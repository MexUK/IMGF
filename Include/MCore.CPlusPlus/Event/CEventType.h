#ifndef CEventType_H
#define CEventType_H

#include "mcore.h"
#include "Type/Types.h"
#include "CInputEventCallbacks.h"
#include "CEventBinder.h"
#include "eEvent.h"

class mcore::CEventBoundFunction;

class mcore::CEventType : public mcore::CEventBinder
{
public:
	CEventType(uint32 uiEventTypeId);

	mcore::CEventBoundFunction*					bindEvent(uint32 uiEventId, void(*pFunction)(void*),		void *pBoundArgument = nullptr, int32 iZOrder = 0, uint32 uiEventTypeIndex = 0);
	mcore::CEventBoundFunction*					bindEvent(uint32 uiEventId, void(*pFunction)(void*,void*),	void *pBoundArgument = nullptr, int32 iZOrder = 0, uint32 uiEventTypeIndex = 0);
	mcore::CEventBoundFunction*					bindEvent(uint32 uiEventId, mcore::CInputEventCallbacks *pObject,	void *pBoundArgument = nullptr, int32 iZOrder = 0, uint32 uiEventTypeIndex = 0);
	void										unbindEvent(mcore::CEventBoundFunction *pEventBoundFunction);
	bool										triggerEvent(uint32 uiEventId, void *pTriggerArgument = nullptr, uint32 uiEventTypeIndex = 0);

	static bool									isEventTypeCursor(eEvent eEventId);
	static bool									isEventTypeKey(eEvent eEventId);
	static bool									isEventTypeRender(eEvent eEventId);

private:
	uint32										m_uiEventTypeId;
};

#endif