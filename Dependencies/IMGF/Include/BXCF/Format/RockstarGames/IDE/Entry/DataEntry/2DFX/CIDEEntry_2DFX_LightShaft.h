#ifndef CIDEEntry_2DFX_LightShaft_H
#define CIDEEntry_2DFX_LightShaft_H

#include "bxcf.h"
#include "Format/RockstarGames/IDE/Entry/DataEntry/CIDEEntry_2DFX.h"
#include <string>

class bxcf::CIDEEntry_2DFX_LightShaft : public bxcf::CIDEEntry_2DFX
{
public:
	CIDEEntry_2DFX_LightShaft(bxcf::CIDEFormat *pIDEFormat) :
		CIDEEntry_2DFX(pIDEFormat, bxcf::_2DFX_LIGHT_SHAFT)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif