#ifndef CIDEEntry_2DFX_Audio_H
#define CIDEEntry_2DFX_Audio_H

#include "bxgi.h"
#include "Format/IDE/Entry/DataEntry/CIDEEntry_2DFX.h"

class bxgi::CIDEEntry_2DFX_Audio : public bxgi::CIDEEntry_2DFX
{
public:
	CIDEEntry_2DFX_Audio(bxgi::CIDEFormat *pIDEFormat) :
		CIDEEntry_2DFX(pIDEFormat, bxgi::_2DFX_AUDIO)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif