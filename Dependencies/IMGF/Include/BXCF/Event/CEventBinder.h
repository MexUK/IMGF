#ifndef CEventBinder_H
#define CEventBinder_H

#include "bxcf.h"
#include "Pool/CVectorPool.h"
#include "CEventBoundFunction.h"

/*

todo:

rename CEventBinder to CEventFunctionStorage

also move bindEvents/unbindEvents interface to a different class?

*/

class bxcf::CEventBinder
{
public:
	// todo virtual void										bindEvents(void) = 0;
	virtual void										bindEvents(void) {};
	// todo virtual void								unbindEvents(void) = 0;

	bxcf::CEventBoundFunction*							storeEventBoundFunction(bxcf::CEventBoundFunction *pEventBoundFunction);
	void												unbindEvents(void);

private:
	bxcf::CVectorPool<bxcf::CEventBoundFunction*>		m_vecEventBoundFunctions;
};

#endif