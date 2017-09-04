#ifndef CIDEEntry_2DFX_WorldPoint_H
#define CIDEEntry_2DFX_WorldPoint_H

#include "bxcf.h"
#include "Format/RockstarGames/IDE/Entry/DataEntry/CIDEEntry_2DFX.h"
#include <string>

class bxcf::CIDEEntry_2DFX_WorldPoint : public bxcf::CIDEEntry_2DFX
{
public:
	CIDEEntry_2DFX_WorldPoint(bxcf::CIDEFormat *pIDEFormat) :
		CIDEEntry_2DFX(pIDEFormat, bxcf::_2DFX_WORLD_POINT)
	{
	}

	void						unserialize(void);
	void						serialize(void);
};

#endif