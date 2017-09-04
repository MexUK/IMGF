#pragma once

#include "nsbxgi.h"
#include "Format/IDE/Entry/DataEntry/IDEEntry_2DFX.h"

class bxgi::IDEEntry_2DFX_SwayableAttr : public bxgi::IDEEntry_2DFX
{
public:
	IDEEntry_2DFX_SwayableAttr(bxgi::IDEFormat *pIDEFormat);

	void						unserialize(void);
	void						serialize(void);
};