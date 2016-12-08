#ifndef CIDEEntry_2DFX_SwayableAttr_H
#define CIDEEntry_2DFX_SwayableAttr_H

#include "mcore.h"
#include "Format/RockstarGames/IDE/Entry/DataEntry/CIDEEntry_2DFX.h"
#include <string>

class mcore::CIDEEntry_2DFX_SwayableAttr : public mcore::CIDEEntry_2DFX
{
public:
	CIDEEntry_2DFX_SwayableAttr(mcore::CIDEFormat *pIDEFormat) :
		CIDEEntry_2DFX(pIDEFormat, mcore::_2DFX_SWAYABLE_ATTR)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif