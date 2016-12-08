#ifndef CIntermediateModel_H
#define CIntermediateModel_H

#include "mcore.h"
#include "Pool/CVectorPool.h"
#include "Data/CIntermediateGeometry.h"
#include <vector>

class mcore::CIntermediateModel : public mcore::CVectorPool<mcore::CIntermediateGeometry*>
{
public:
	void								unload(void) {}
};

#endif