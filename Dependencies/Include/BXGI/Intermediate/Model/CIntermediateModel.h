#pragma once

#include "nsbxgi.h"
#include "Pool/CVectorPool.h"
#include "Data/CIntermediateGeometry.h"

class bxgi::CIntermediateModel : public bxcf::CVectorPool<bxgi::CIntermediateGeometry*>
{
public:
	void								unload(void) {}
};