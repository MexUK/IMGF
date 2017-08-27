#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "Format/RW/Entries/C2dEffect.h"

class bxgi::CRWEntry_2dEffect_SunGlare : public bxgi::C2dEffect
{
public:
	CRWEntry_2dEffect_SunGlare(void);

	void							unserialize(void);
	void							serialize(void);
};