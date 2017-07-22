#ifndef CIDEEntry_2DFX_ScrollBar_H
#define CIDEEntry_2DFX_ScrollBar_H

#include "Format/RockstarGames/IDE/Entry/DataEntry/CIDEEntry_2DFX.h"
#include <string>

class bxa::CIDEEntry_2DFX_ScrollBar : public bxa::CIDEEntry_2DFX
{
public:
	CIDEEntry_2DFX_ScrollBar(bxa::CIDEFormat *pIDEFormat) :
		CIDEEntry_2DFX(pIDEFormat, bxa::_2DFX_SCROLL_BAR)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif