#ifndef CIDEEntry_2DFX_LightShaft_H
#define CIDEEntry_2DFX_LightShaft_H

#include "mcore.h"
#include "Format/RockstarGames/IDE/Entry/DataEntry/CIDEEntry_2DFX.h"
#include <string>

class mcore::CIDEEntry_2DFX_LightShaft : public mcore::CIDEEntry_2DFX
{
public:
	CIDEEntry_2DFX_LightShaft(mcore::CIDEFormat *pIDEFormat) :
		CIDEEntry_2DFX(pIDEFormat, mcore::_2DFX_LIGHT_SHAFT)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif