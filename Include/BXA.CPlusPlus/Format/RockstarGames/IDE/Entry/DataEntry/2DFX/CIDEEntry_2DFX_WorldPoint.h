#ifndef CIDEEntry_2DFX_WorldPoint_H
#define CIDEEntry_2DFX_WorldPoint_H

#include "BXA.h"
#include "Format/RockstarGames/IDE/Entry/DataEntry/CIDEEntry_2DFX.h"
#include <string>

class bxa::CIDEEntry_2DFX_WorldPoint : public bxa::CIDEEntry_2DFX
{
public:
	CIDEEntry_2DFX_WorldPoint(bxa::CIDEFormat *pIDEFormat) :
		CIDEEntry_2DFX(pIDEFormat, bxa::_2DFX_WORLD_POINT)
	{
	}

	void						unserialize(void);
	void						serialize(void);
};

#endif