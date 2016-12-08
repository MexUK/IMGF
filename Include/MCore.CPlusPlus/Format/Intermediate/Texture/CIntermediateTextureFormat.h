#ifndef CIntermediateTextureFormat_H
#define CIntermediateTextureFormat_H

#include "mcore.h"
#include "Pool/CVectorPool.h"
#include "CIntermediateTexture.h"

class mcore::CIntermediateTextureFormat : public mcore::CVectorPool<mcore::CIntermediateTexture*>
{
public:
	void						unload(void);
};

#endif