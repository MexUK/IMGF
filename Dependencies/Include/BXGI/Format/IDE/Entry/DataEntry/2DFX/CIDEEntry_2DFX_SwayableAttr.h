#pragma once

#include "nsbxgi.h"
#include "Format/IDE/Entry/DataEntry/CIDEEntry_2DFX.h"

class bxgi::CIDEEntry_2DFX_SwayableAttr : public bxgi::CIDEEntry_2DFX
{
public:
	CIDEEntry_2DFX_SwayableAttr(bxgi::CIDEFormat *pIDEFormat);

	void						unserialize(void);
	void						serialize(void);
};