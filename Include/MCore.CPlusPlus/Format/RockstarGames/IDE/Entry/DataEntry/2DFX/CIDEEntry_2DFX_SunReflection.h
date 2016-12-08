#ifndef CIDEEntry_2DFX_SunReflection_H
#define CIDEEntry_2DFX_SunReflection_H

#include "mcore.h"
#include "Format/RockstarGames/IDE/Entry/DataEntry/CIDEEntry_2DFX.h"

class mcore::CIDEEntry_2DFX_SunReflection : public mcore::CIDEEntry_2DFX
{
public:
	CIDEEntry_2DFX_SunReflection(mcore::CIDEFormat *pIDEFormat) :
		CIDEEntry_2DFX(pIDEFormat, mcore::_2DFX_SUN_REFLECTION)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif