#ifndef CIntermediateTextureFormat_H
#define CIntermediateTextureFormat_H

#include "bxcf.h"
#include "Pool/CVectorPool.h"
#include "CIntermediateTexture.h"

class bxcf::CIntermediateTextureFormat : public bxcf::CVectorPool<bxcf::CIntermediateTexture*>
{
public:
	void						unload(void);
};

#endif