#ifndef CIDEEntry_2DFX_ProcObject_H
#define CIDEEntry_2DFX_ProcObject_H

#include "bxgi.h"
#include "Format/IDE/Entry/DataEntry/CIDEEntry_2DFX.h"

class bxgi::CIDEEntry_2DFX_ProcObject : public bxgi::CIDEEntry_2DFX
{
public:
	CIDEEntry_2DFX_ProcObject(bxgi::CIDEFormat *pIDEFormat) :
		CIDEEntry_2DFX(pIDEFormat, bxgi::_2DFX_PROC_OBJECT)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif