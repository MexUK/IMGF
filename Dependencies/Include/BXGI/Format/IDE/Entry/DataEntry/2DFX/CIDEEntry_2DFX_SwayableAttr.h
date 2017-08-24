#ifndef CIDEEntry_2DFX_SwayableAttr_H
#define CIDEEntry_2DFX_SwayableAttr_H

#include "bxgi.h"
#include "Format/IDE/Entry/DataEntry/CIDEEntry_2DFX.h"

class bxgi::CIDEEntry_2DFX_SwayableAttr : public bxgi::CIDEEntry_2DFX
{
public:
	CIDEEntry_2DFX_SwayableAttr(bxgi::CIDEFormat *pIDEFormat) :
		CIDEEntry_2DFX(pIDEFormat, bxgi::_2DFX_SWAYABLE_ATTR)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif