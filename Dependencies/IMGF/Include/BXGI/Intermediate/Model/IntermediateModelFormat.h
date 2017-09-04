#pragma once

#include "nsbxgi.h"
#include "Pool/VectorPool.h"
#include "IntermediateModel.h"

class bxgi::IntermediateModelFormat : public bxcf::VectorPool<bxgi::IntermediateModel*>
{
public:
	void								unload(void);
};