#ifndef CIDEEntry_2DFX_Audio_H
#define CIDEEntry_2DFX_Audio_H

#include "bxa.h"
#include "Format/RockstarGames/IDE/Entry/DataEntry/CIDEEntry_2DFX.h"
#include <string>

class bxa::CIDEEntry_2DFX_Audio : public bxa::CIDEEntry_2DFX
{
public:
	CIDEEntry_2DFX_Audio(bxa::CIDEFormat *pIDEFormat) :
		CIDEEntry_2DFX(pIDEFormat, bxa::_2DFX_AUDIO)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif