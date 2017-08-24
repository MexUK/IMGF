#ifndef CIntermediateModel_H
#define CIntermediateModel_H

#include "bxgi.h"
#include "Pool/CVectorPool.h"
#include "Data/CIntermediateGeometry.h"

class bxgi::CIntermediateModel : public bxcf::CVectorPool<bxgi::CIntermediateGeometry*>
{
public:
	void								unload(void) {}
};

#endif