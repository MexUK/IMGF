#ifndef CIDEEntry_2DFX_SunReflection_H
#define CIDEEntry_2DFX_SunReflection_H

#include "bxgi.h"
#include "Format/IDE/Entry/DataEntry/CIDEEntry_2DFX.h"

class bxgi::CIDEEntry_2DFX_SunReflection : public bxgi::CIDEEntry_2DFX
{
public:
	CIDEEntry_2DFX_SunReflection(bxgi::CIDEFormat *pIDEFormat) :
		CIDEEntry_2DFX(pIDEFormat, bxgi::_2DFX_SUN_REFLECTION)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif