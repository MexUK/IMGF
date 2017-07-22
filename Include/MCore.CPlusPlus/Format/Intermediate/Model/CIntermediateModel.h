#ifndef CIntermediateModel_H
#define CIntermediateModel_H

#include "bxa.h"
#include "Pool/CVectorPool.h"
#include "Data/CIntermediateGeometry.h"
#include <vector>

class bxa::CIntermediateModel : public bxa::CVectorPool<bxa::CIntermediateGeometry*>
{
public:
	void								unload(void) {}
};

#endif