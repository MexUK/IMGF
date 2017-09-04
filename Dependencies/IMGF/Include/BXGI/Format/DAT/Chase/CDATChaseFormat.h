#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "Format/CFormat.h"
#include "Pool/CVectorPool.h"
#include "CDATChaseEntry.h"
#include <vector>

class bxgi::CDATChaseFormat : public bxcf::CFormat, public bxcf::CVectorPool<bxgi::CDATChaseEntry*>
{
public:
	CDATChaseFormat(void);
	
	void					unserialize(void);
	void					serialize(void);
};