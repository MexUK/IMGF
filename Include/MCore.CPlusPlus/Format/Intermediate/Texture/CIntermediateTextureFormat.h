#ifndef CIntermediateTextureFormat_H
#define CIntermediateTextureFormat_H

#include "bxa.h"
#include "Pool/CVectorPool.h"
#include "CIntermediateTexture.h"

class bxa::CIntermediateTextureFormat : public bxa::CVectorPool<bxa::CIntermediateTexture*>
{
public:
	void						unload(void);
};

#endif