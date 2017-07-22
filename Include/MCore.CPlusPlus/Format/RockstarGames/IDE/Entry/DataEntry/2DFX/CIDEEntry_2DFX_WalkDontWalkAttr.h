#ifndef CIDEEntry_2DFX_WalkDontWalkAttr_H
#define CIDEEntry_2DFX_WalkDontWalkAttr_H

#include "bxa.h"
#include "Format/RockstarGames/IDE/Entry/DataEntry/CIDEEntry_2DFX.h"
#include <string>

class bxa::CIDEEntry_2DFX_WalkDontWalkAttr : public bxa::CIDEEntry_2DFX
{
public:
	CIDEEntry_2DFX_WalkDontWalkAttr(bxa::CIDEFormat *pIDEFormat) :
		CIDEEntry_2DFX(pIDEFormat, bxa::_2DFX_WALK_DONT_WALK_ATTR)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif