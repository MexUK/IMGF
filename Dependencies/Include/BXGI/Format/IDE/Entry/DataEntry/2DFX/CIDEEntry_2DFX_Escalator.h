#ifndef CIDEEntry_2DFX_Escalator_H
#define CIDEEntry_2DFX_Escalator_H

#include "bxgi.h"
#include "Format/IDE/Entry/DataEntry/CIDEEntry_2DFX.h"

class bxgi::CIDEEntry_2DFX_Escalator : public bxgi::CIDEEntry_2DFX
{
public:
	CIDEEntry_2DFX_Escalator(bxgi::CIDEFormat *pIDEFormat) :
		CIDEEntry_2DFX(pIDEFormat, bxgi::_2DFX_ESCALATOR)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif