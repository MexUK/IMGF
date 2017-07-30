#ifndef CIDEEntry_2DFX_SunReflection_H
#define CIDEEntry_2DFX_SunReflection_H

#include "bxcf.h"
#include "Format/RockstarGames/IDE/Entry/DataEntry/CIDEEntry_2DFX.h"

class bxcf::CIDEEntry_2DFX_SunReflection : public bxcf::CIDEEntry_2DFX
{
public:
	CIDEEntry_2DFX_SunReflection(bxcf::CIDEFormat *pIDEFormat) :
		CIDEEntry_2DFX(pIDEFormat, bxcf::_2DFX_SUN_REFLECTION)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif