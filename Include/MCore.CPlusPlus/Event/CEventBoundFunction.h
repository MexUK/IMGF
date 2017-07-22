#ifndef CEventBoundFunction_H
#define CEventBoundFunction_H

#include "bxa.h"
#include "Type/Types.h"
#include "eEvent.h"
#include "eEventFunctionType.h"
#include "CInputEventCallbacks.h"

class bxa::CEventBoundFunction
{
public:
	CEventBoundFunction(void);

	void					unload(void) {}

	void					onEventTriggered(uint32 uiEventId, void *pTriggerArgument);
	void					triggerObjectCallback(uint32 uiEventId, void *pTriggerArgument);

	void					setEventTypeId(uint32 uiEventTypeId) { m_uiEventTypeId = uiEventTypeId; }
	uint32					getEventTypeId(void) { return m_uiEventTypeId; }

	void					setEventTypeIndex(uint32 uiEventTypeIndex) { m_uiEventTypeIndex = uiEventTypeIndex; }
	uint32					getEventTypeIndex(void) { return m_uiEventTypeIndex; }

	void					setEventId(uint32 uiEventId) { m_uiEventId = uiEventId; }
	uint32					getEventId(void) { return m_uiEventId; }

	void					setZIndex(int32 iZIndex) { m_iZIndex = iZIndex; }
	int32					getZIndex(void) { return m_iZIndex; }

	void					setEventFunctionType(eEventFunctionType eFunctionType) { m_eEventFunctionType = eFunctionType; }
	eEventFunctionType		getEventFunctionType(void) { return m_eEventFunctionType; }

	void					setFunction(void(*fFunction)(void*)) { m_pFunction_1Arg = fFunction; }
	void					setFunction(void(*fFunction)(void*,void*)) { m_pFunction_2Args = fFunction; }
	void					(*getFunction1Arg(void))(void*) { return m_pFunction_1Arg; }
	void					(*getFunction2Args(void))(void*,void*) { return m_pFunction_2Args; }

	void					setCallbackObject(CInputEventCallbacks *pCallbackObject) { m_pCallbackObject = pCallbackObject; }
	CInputEventCallbacks*	getCallbackObject(void) { return m_pCallbackObject; }

	void					setFunctionBoundArgument(void* pFunctionBoundArgument) { m_pFunctionBoundArgument = pFunctionBoundArgument; }	// 2 event argument types are used, bound arg and trigger arg
	void*					getFunctionBoundArgument(void) { return m_pFunctionBoundArgument; }												// 2 event argument types are used, bound arg and trigger arg

private:
	uint32					m_uiEventTypeId;
	uint32					m_uiEventTypeIndex;
	uint32					m_uiEventId;
	int32					m_iZIndex;
	eEventFunctionType		m_eEventFunctionType;
	void					(*m_pFunction_1Arg)(void*);
	void					(*m_pFunction_2Args)(void*,void*);
	void*					m_pFunctionBoundArgument;
	CInputEventCallbacks*	m_pCallbackObject;
};

#endif