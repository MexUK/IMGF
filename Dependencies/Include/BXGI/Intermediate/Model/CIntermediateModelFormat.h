#pragma once

#include "nsbxgi.h"
#include "Pool/CVectorPool.h"
#include "CIntermediateModel.h"

class bxgi::CIntermediateModelFormat : public bxcf::CVectorPool<bxgi::CIntermediateModel*>
{
public:
	void								unload(void);
};