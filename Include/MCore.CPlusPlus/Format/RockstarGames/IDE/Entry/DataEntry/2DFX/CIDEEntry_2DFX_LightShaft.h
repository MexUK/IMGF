#ifndef CIDEEntry_2DFX_LightShaft_H
#define CIDEEntry_2DFX_LightShaft_H

#include "bxa.h"
#include "Format/RockstarGames/IDE/Entry/DataEntry/CIDEEntry_2DFX.h"
#include <string>

class bxa::CIDEEntry_2DFX_LightShaft : public bxa::CIDEEntry_2DFX
{
public:
	CIDEEntry_2DFX_LightShaft(bxa::CIDEFormat *pIDEFormat) :
		CIDEEntry_2DFX(pIDEFormat, bxa::_2DFX_LIGHT_SHAFT)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif