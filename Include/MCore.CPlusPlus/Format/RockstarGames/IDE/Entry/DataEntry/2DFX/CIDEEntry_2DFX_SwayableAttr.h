#ifndef CIDEEntry_2DFX_SwayableAttr_H
#define CIDEEntry_2DFX_SwayableAttr_H

#include "bxa.h"
#include "Format/RockstarGames/IDE/Entry/DataEntry/CIDEEntry_2DFX.h"
#include <string>

class bxa::CIDEEntry_2DFX_SwayableAttr : public bxa::CIDEEntry_2DFX
{
public:
	CIDEEntry_2DFX_SwayableAttr(bxa::CIDEFormat *pIDEFormat) :
		CIDEEntry_2DFX(pIDEFormat, bxa::_2DFX_SWAYABLE_ATTR)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif