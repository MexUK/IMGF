#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "Format/Format.h"
#include "Pool/VectorPool.h"
#include "DATScriptPathEntry.h"

class bxgi::DATScriptPathFormat : public bxcf::Format, public bxcf::VectorPool<bxgi::DATScriptPathEntry*>
{
public:
	DATScriptPathFormat(void);
	
	void					unserialize(void);
	void					serialize(void); // todo
};