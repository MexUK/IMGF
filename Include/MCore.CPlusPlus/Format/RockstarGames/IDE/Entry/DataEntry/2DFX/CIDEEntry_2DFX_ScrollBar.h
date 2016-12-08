#ifndef CIDEEntry_2DFX_ScrollBar_H
#define CIDEEntry_2DFX_ScrollBar_H

#include "Format/RockstarGames/IDE/Entry/DataEntry/CIDEEntry_2DFX.h"
#include <string>

class mcore::CIDEEntry_2DFX_ScrollBar : public mcore::CIDEEntry_2DFX
{
public:
	CIDEEntry_2DFX_ScrollBar(mcore::CIDEFormat *pIDEFormat) :
		CIDEEntry_2DFX(pIDEFormat, mcore::_2DFX_SCROLL_BAR)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif