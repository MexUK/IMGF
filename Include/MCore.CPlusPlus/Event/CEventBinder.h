#ifndef CEventBinder_H
#define CEventBinder_H

#include "mcore.h"
#include "Pool/CVectorPool.h"
#include "CEventBoundFunction.h"

class mcore::CEventBinder
{
public:
	virtual void							bindEvents(void) = 0;
	void									unbindEvents(void);
	void									storeEventBoundFunction(CEventBoundFunction *pEventBoundFunction);

private:
	mcore::CVectorPool<CEventBoundFunction*>		m_vecEventBoundFunctions;
};

#endif