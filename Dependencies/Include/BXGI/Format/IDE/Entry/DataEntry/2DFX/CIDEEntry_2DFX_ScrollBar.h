#ifndef CIDEEntry_2DFX_ScrollBar_H
#define CIDEEntry_2DFX_ScrollBar_H

#include "Format/IDE/Entry/DataEntry/CIDEEntry_2DFX.h"

class bxgi::CIDEEntry_2DFX_ScrollBar : public bxgi::CIDEEntry_2DFX
{
public:
	CIDEEntry_2DFX_ScrollBar(bxgi::CIDEFormat *pIDEFormat) :
		CIDEEntry_2DFX(pIDEFormat, bxgi::_2DFX_SCROLL_BAR)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif