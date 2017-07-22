#ifndef CEventBinder_H
#define CEventBinder_H

#include "bxa.h"
#include "Pool/CVectorPool.h"
#include "CEventBoundFunction.h"

/*

todo:

rename CEventBinder to CEventFunctionStorage

also move bindEvents/unbindEvents interface to a different class?

*/

class bxa::CEventBinder
{
public:
	// todo virtual void										bindEvents(void) = 0;
	virtual void										bindEvents(void) {};
	// todo virtual void								unbindEvents(void) = 0;

	bxa::CEventBoundFunction*							storeEventBoundFunction(bxa::CEventBoundFunction *pEventBoundFunction);
	void												unbindEvents(void);

private:
	bxa::CVectorPool<bxa::CEventBoundFunction*>		m_vecEventBoundFunctions;
};

#endif