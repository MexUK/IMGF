#ifndef CIDEEntry_2DFX_Audio_H
#define CIDEEntry_2DFX_Audio_H

#include "mcore.h"
#include "Format/RockstarGames/IDE/Entry/DataEntry/CIDEEntry_2DFX.h"
#include <string>

class mcore::CIDEEntry_2DFX_Audio : public mcore::CIDEEntry_2DFX
{
public:
	CIDEEntry_2DFX_Audio(mcore::CIDEFormat *pIDEFormat) :
		CIDEEntry_2DFX(pIDEFormat, mcore::_2DFX_AUDIO)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif