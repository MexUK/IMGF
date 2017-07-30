#ifndef CIDEEntry_2DFX_ProcObject_H
#define CIDEEntry_2DFX_ProcObject_H

#include "bxcf.h"
#include "Format/RockstarGames/IDE/Entry/DataEntry/CIDEEntry_2DFX.h"
#include <string>

class bxcf::CIDEEntry_2DFX_ProcObject : public bxcf::CIDEEntry_2DFX
{
public:
	CIDEEntry_2DFX_ProcObject(bxcf::CIDEFormat *pIDEFormat) :
		CIDEEntry_2DFX(pIDEFormat, bxcf::_2DFX_PROC_OBJECT)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif