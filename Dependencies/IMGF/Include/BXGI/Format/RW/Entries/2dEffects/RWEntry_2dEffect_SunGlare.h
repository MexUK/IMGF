#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "Format/RW/Entries/_2dEffect.h"

class bxgi::RWEntry_2dEffect_SunGlare : public bxgi::_2dEffect
{
public:
	RWEntry_2dEffect_SunGlare(void);

	void							unserialize(void);
	void							serialize(void);
};