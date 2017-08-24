#ifndef CIntermediateTextureFormat_H
#define CIntermediateTextureFormat_H

#include "bxgi.h"
#include "Pool/CVectorPool.h"
#include "CIntermediateTexture.h"

class bxgi::CIntermediateTextureFormat : public bxcf::CVectorPool<bxgi::CIntermediateTexture*>
{
public:
	void						unload(void);
};

#endif