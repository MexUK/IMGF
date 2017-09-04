#pragma once

#include "nsbxgi.h"
#include "Pool/VectorPool.h"
#include "IntermediateTexture.h"

class bxgi::IntermediateTextureFormat : public bxcf::VectorPool<bxgi::IntermediateTexture*>
{
public:
	void						unload(void);
};