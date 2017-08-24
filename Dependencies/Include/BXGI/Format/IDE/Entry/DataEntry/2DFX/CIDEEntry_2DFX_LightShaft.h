#ifndef CIDEEntry_2DFX_LightShaft_H
#define CIDEEntry_2DFX_LightShaft_H

#include "bxgi.h"
#include "Format/IDE/Entry/DataEntry/CIDEEntry_2DFX.h"

class bxgi::CIDEEntry_2DFX_LightShaft : public bxgi::CIDEEntry_2DFX
{
public:
	CIDEEntry_2DFX_LightShaft(bxgi::CIDEFormat *pIDEFormat) :
		CIDEEntry_2DFX(pIDEFormat, bxgi::_2DFX_LIGHT_SHAFT)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif