#pragma once

#include "Format/IDE/Entry/DataEntry/IDEEntry_2DFX.h"

class bxgi::IDEEntry_2DFX_ScrollBar : public bxgi::IDEEntry_2DFX
{
public:
	IDEEntry_2DFX_ScrollBar(bxgi::IDEFormat *pIDEFormat);

	void						unserialize(void);
	void						serialize(void);
};