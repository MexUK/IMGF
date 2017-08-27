#pragma once

#include "Format/IDE/Entry/DataEntry/CIDEEntry_2DFX.h"

class bxgi::CIDEEntry_2DFX_ScrollBar : public bxgi::CIDEEntry_2DFX
{
public:
	CIDEEntry_2DFX_ScrollBar(bxgi::CIDEFormat *pIDEFormat);

	void						unserialize(void);
	void						serialize(void);
};