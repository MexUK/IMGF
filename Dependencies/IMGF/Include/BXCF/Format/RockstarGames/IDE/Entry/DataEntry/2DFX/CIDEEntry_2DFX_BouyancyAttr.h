#ifndef CIDEEntry_2DFX_BouyancyAttr_H
#define CIDEEntry_2DFX_BouyancyAttr_H

#include "bxcf.h"
#include "Format/RockstarGames/IDE/Entry/DataEntry/CIDEEntry_2DFX.h"
#include <string>

class bxcf::CIDEEntry_2DFX_BouyancyAttr : public bxcf::CIDEEntry_2DFX
{
public:
	CIDEEntry_2DFX_BouyancyAttr(bxcf::CIDEFormat *pIDEFormat) :
		CIDEEntry_2DFX(pIDEFormat, bxcf::_2DFX_BOUYANCY_ATTR)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif