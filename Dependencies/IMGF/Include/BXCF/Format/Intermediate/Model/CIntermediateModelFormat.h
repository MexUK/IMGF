#ifndef CIntermediateModelFormat_H
#define CIntermediateModelFormat_H

#include "bxcf.h"
#include "Pool/CVectorPool.h"
#include "CIntermediateModel.h"
#include <vector>

class bxcf::CIntermediateModelFormat : public bxcf::CVectorPool<bxcf::CIntermediateModel*>
{
public:
	void								unload(void);
};

#endif