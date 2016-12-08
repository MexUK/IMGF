#ifndef CEventManager_H
#define CEventManager_H

#include "mcore.h"
#include "Type/Types.h"
#include "Object/CSingleton.h"
#include "eEventType.h"
#include "Type/Vector/CVector2i32.h"
#include "Type/Vector/CPoint2D.h"
#include "CInputEventCallbacks.h"
#include <string>
#include <vector>
#include <unordered_map>

class mcore::CEventBoundFunction;

class mcore::CEventManager : public mcore::CSingleton<CEventManager>
{
public:
	CEventManager(void) :
		m_bDefaultActionPrevented(false),
		m_bEventHogged(false)
	{
	}

	// EVENT_TYPE_GENERAL, 0
	mcore::CEventBoundFunction*					bindEvent(uint32 uiEventId, void(*fEventFunction)(void*),		void *pBoundArgument = nullptr, int32 iZIndex = 0);	// negative z-index's trigger before positive ones
	mcore::CEventBoundFunction*					bindEvent(uint32 uiEventId, void(*fEventFunction)(void*,void*), void *pBoundArgument = nullptr, int32 iZIndex = 0);	// negative z-index's trigger before positive ones
	mcore::CEventBoundFunction*					bindEvent(uint32 uiEventId, CInputEventCallbacks *pObject,		void *pBoundArgument = nullptr, int32 iZIndex = 0);	// negative z-index's trigger before positive ones
	bool										doesEventExist(uint32 uiEventId);
	uint32										getBoundFunctionCount(uint32 uiEventId);
	bool										triggerEvent(uint32 uiEventId, void *pTriggerArgument = nullptr);

	// EVENT_TYPE_*, *
	mcore::CEventBoundFunction*					bindEvent(uint32 uiEventTypeId, uint32 uiEventTypeIndex, uint32 uiEventId, void(*fEventFunction)(void*),		void *pBoundArgument = nullptr, int32 iZIndex = 0);	// negative z-index's trigger before positive ones
	mcore::CEventBoundFunction*					bindEvent(uint32 uiEventTypeId, uint32 uiEventTypeIndex, uint32 uiEventId, void(*fEventFunction)(void*,void*),	void *pBoundArgument = nullptr, int32 iZIndex = 0);	// negative z-index's trigger before positive ones
	mcore::CEventBoundFunction*					bindEvent(uint32 uiEventTypeId, uint32 uiEventTypeIndex, uint32 uiEventId, CInputEventCallbacks *pObject,		void *pBoundArgument = nullptr, int32 iZIndex = 0);	// negative z-index's trigger before positive ones
	bool										unbindEvent(mcore::CEventBoundFunction *pEventBoundFunction);
	bool										doesEventExist(uint32 uiEventTypeId, uint32 uiEventTypeIndex, uint32 uiEventId);
	uint32										getBoundFunctionCount(uint32 uiEventTypeId, uint32 uiEventTypeIndex, uint32 uiEventId);
	bool										triggerEvent(uint32 uiEventTypeId, uint32 uiEventTypeIndex, uint32 uiEventId, void *pTriggerArgument = nullptr);

	// CEventManager continued
	void										setLatestCursorPosition(mcore::CPoint2D& vecLatestCursorPosition) { m_vecLatestCursorPosition = vecLatestCursorPosition; }
	mcore::CPoint2D&									getLatestCursorPosition(void) { return m_vecLatestCursorPosition; }

	void										setLatestScreenCursorPosition(mcore::CPoint2D& vecLatestScreenCursorPosition) { m_vecLatestScreenCursorPosition = vecLatestScreenCursorPosition; }
	mcore::CPoint2D&									getLatestScreenCursorPosition(void) { return m_vecLatestScreenCursorPosition; }

	void										setPreviousCursorPosition(mcore::CPoint2D& vecPreviousCursorPosition) { m_vecPreviousCursorPosition = vecPreviousCursorPosition; }
	mcore::CPoint2D&									getPreviousCursorPosition(void) { return m_vecPreviousCursorPosition; }

	void										setPreviousScreenCursorPosition(mcore::CPoint2D& vecPreviousScreenCursorPosition) { m_vecPreviousScreenCursorPosition = vecPreviousScreenCursorPosition; }
	mcore::CPoint2D&									getPreviousScreenCursorPosition(void) { return m_vecPreviousScreenCursorPosition; }

	void										setScreenCursorMoveDifference(mcore::CVector2i32& vecScreenCursorMoveDifference) { m_vecScreenCursorMoveDifference = vecScreenCursorMoveDifference; }
	mcore::CVector2i32&								getScreenCursorMoveDifference(void) { return m_vecScreenCursorMoveDifference; }

	void										setDefaultActionPrevented(bool bDefaultActionPrevented) { m_bDefaultActionPrevented = bDefaultActionPrevented; }
	bool										isDefaultActionPrevented(void) { return m_bDefaultActionPrevented; }

	void										setEventHogged(bool bEventHogged) { m_bEventHogged = bEventHogged; }
	bool										isEventHogged(void) { return m_bEventHogged; }

private:
	mcore::CEventBoundFunction*					createEventBoundFunctionObject(uint32 uiEventTypeId, uint32 uiEventTypeIndex, uint32 uiEventId, void *pBoundArgument, int32 iZIndex);

	uint32										getInsertionIndexForEventBoundFunction(mcore::CEventBoundFunction *pEventBoundFunction);

private:
	uint8															m_bDefaultActionPrevented	: 1;
	uint8															m_bEventHogged				: 1;
	mcore::CPoint2D														m_vecLatestCursorPosition;
	mcore::CPoint2D														m_vecLatestScreenCursorPosition;
	mcore::CPoint2D														m_vecPreviousCursorPosition;
	mcore::CPoint2D														m_vecPreviousScreenCursorPosition;
	mcore::CVector2i32														m_vecScreenCursorMoveDifference;
	std::unordered_map<
		uint32,
		std::unordered_map<
			uint32,
			std::unordered_map<
				uint32,
				std::vector<mcore::CEventBoundFunction*>
			>
		>
	>																m_umapEventFunctions;
};

#endif