#ifndef CEventBinder_H
#define CEventBinder_H

#include "mcore.h"
#include "Pool/CVectorPool.h"
#include "CEventBoundFunction.h"

/*

todo:

rename CEventBinder to CEventFunctionStorage

also move bindEvents/unbindEvents interface to a different class?

*/

class mcore::CEventBinder
{
public:
	// todo virtual void										bindEvents(void) = 0;
	virtual void										bindEvents(void) {};
	// todo virtual void								unbindEvents(void) = 0;

	mcore::CEventBoundFunction*							storeEventBoundFunction(mcore::CEventBoundFunction *pEventBoundFunction);
	void												unbindEvents(void);

private:
	mcore::CVectorPool<mcore::CEventBoundFunction*>		m_vecEventBoundFunctions;
};

#endif