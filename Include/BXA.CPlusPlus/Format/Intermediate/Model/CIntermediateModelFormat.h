#ifndef CIntermediateModelFormat_H
#define CIntermediateModelFormat_H

#include "BXA.h"
#include "Pool/CVectorPool.h"
#include "CIntermediateModel.h"
#include <vector>

class bxa::CIntermediateModelFormat : public bxa::CVectorPool<bxa::CIntermediateModel*>
{
public:
	void								unload(void);
};

#endif