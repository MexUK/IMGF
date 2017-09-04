#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "Format/Format.h"
#include "DATAnimgrpSection.h"

class bxgi::DATAnimgrpFormat : public bxcf::Format, public bxcf::VectorPool<bxgi::DATAnimgrpSection*>
{
public:
	DATAnimgrpFormat(void);
	
	void					unserialize(void);
	void					serialize(void);
};