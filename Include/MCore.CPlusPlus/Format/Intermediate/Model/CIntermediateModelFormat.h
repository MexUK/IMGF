#ifndef CIntermediateModelFormat_H
#define CIntermediateModelFormat_H

#include "mcore.h"
#include "Pool/CVectorPool.h"
#include "CIntermediateModel.h"
#include <vector>

class mcore::CIntermediateModelFormat : public mcore::CVectorPool<mcore::CIntermediateModel*>
{
public:
	void								unload(void);
};

#endif