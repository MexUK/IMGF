#pragma once

#include "nsbxgi.h"
#include "Pool/VectorPool.h"
#include "Data/IntermediateGeometry.h"

class bxgi::IntermediateModel : public bxcf::VectorPool<bxgi::IntermediateGeometry*>
{
public:
	void								unload(void) {}
};