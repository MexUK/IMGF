#ifndef CIDEEntry_2DFX_SunReflection_H
#define CIDEEntry_2DFX_SunReflection_H

#include "bxa.h"
#include "Format/RockstarGames/IDE/Entry/DataEntry/CIDEEntry_2DFX.h"

class bxa::CIDEEntry_2DFX_SunReflection : public bxa::CIDEEntry_2DFX
{
public:
	CIDEEntry_2DFX_SunReflection(bxa::CIDEFormat *pIDEFormat) :
		CIDEEntry_2DFX(pIDEFormat, bxa::_2DFX_SUN_REFLECTION)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif