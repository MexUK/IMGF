#ifndef CIDEEntry_2DFX_Audio_H
#define CIDEEntry_2DFX_Audio_H

#include "bxcf.h"
#include "Format/RockstarGames/IDE/Entry/DataEntry/CIDEEntry_2DFX.h"
#include <string>

class bxcf::CIDEEntry_2DFX_Audio : public bxcf::CIDEEntry_2DFX
{
public:
	CIDEEntry_2DFX_Audio(bxcf::CIDEFormat *pIDEFormat) :
		CIDEEntry_2DFX(pIDEFormat, bxcf::_2DFX_AUDIO)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif