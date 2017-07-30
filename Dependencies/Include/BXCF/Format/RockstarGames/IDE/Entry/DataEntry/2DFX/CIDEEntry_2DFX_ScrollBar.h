#ifndef CIDEEntry_2DFX_ScrollBar_H
#define CIDEEntry_2DFX_ScrollBar_H

#include "Format/RockstarGames/IDE/Entry/DataEntry/CIDEEntry_2DFX.h"
#include <string>

class bxcf::CIDEEntry_2DFX_ScrollBar : public bxcf::CIDEEntry_2DFX
{
public:
	CIDEEntry_2DFX_ScrollBar(bxcf::CIDEFormat *pIDEFormat) :
		CIDEEntry_2DFX(pIDEFormat, bxcf::_2DFX_SCROLL_BAR)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif