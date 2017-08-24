#ifndef CIDEEntry_2DFX_BouyancyAttr_H
#define CIDEEntry_2DFX_BouyancyAttr_H

#include "bxgi.h"
#include "Format/IDE/Entry/DataEntry/CIDEEntry_2DFX.h"

class bxgi::CIDEEntry_2DFX_BouyancyAttr : public bxgi::CIDEEntry_2DFX
{
public:
	CIDEEntry_2DFX_BouyancyAttr(bxgi::CIDEFormat *pIDEFormat) :
		CIDEEntry_2DFX(pIDEFormat, bxgi::_2DFX_BOUYANCY_ATTR)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif