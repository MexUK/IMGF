#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "Format/Format.h"
#include "Pool/VectorPool.h"
#include "DATChaseEntry.h"
#include <vector>

class bxgi::DATChaseFormat : public bxcf::Format, public bxcf::VectorPool<bxgi::DATChaseEntry*>
{
public:
	DATChaseFormat(void);
	
	void					unserialize(void);
	void					serialize(void);
};