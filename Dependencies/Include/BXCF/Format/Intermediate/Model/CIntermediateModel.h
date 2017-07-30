#ifndef CIntermediateModel_H
#define CIntermediateModel_H

#include "bxcf.h"
#include "Pool/CVectorPool.h"
#include "Data/CIntermediateGeometry.h"
#include <vector>

class bxcf::CIntermediateModel : public bxcf::CVectorPool<bxcf::CIntermediateGeometry*>
{
public:
	void								unload(void) {}
};

#endif