#ifndef CIDEEntry_2DFX_WorldPoint_H
#define CIDEEntry_2DFX_WorldPoint_H

#include "mcore.h"
#include "Format/RockstarGames/IDE/Entry/DataEntry/CIDEEntry_2DFX.h"
#include <string>

class mcore::CIDEEntry_2DFX_WorldPoint : public mcore::CIDEEntry_2DFX
{
public:
	CIDEEntry_2DFX_WorldPoint(mcore::CIDEFormat *pIDEFormat) :
		CIDEEntry_2DFX(pIDEFormat, mcore::_2DFX_WORLD_POINT)
	{
	}

	void						unserialize(void);
	void						serialize(void);
};

#endif