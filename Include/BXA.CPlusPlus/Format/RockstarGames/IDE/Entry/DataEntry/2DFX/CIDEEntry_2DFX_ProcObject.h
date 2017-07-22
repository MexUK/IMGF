#ifndef CIDEEntry_2DFX_ProcObject_H
#define CIDEEntry_2DFX_ProcObject_H

#include "BXA.h"
#include "Format/RockstarGames/IDE/Entry/DataEntry/CIDEEntry_2DFX.h"
#include <string>

class bxa::CIDEEntry_2DFX_ProcObject : public bxa::CIDEEntry_2DFX
{
public:
	CIDEEntry_2DFX_ProcObject(bxa::CIDEFormat *pIDEFormat) :
		CIDEEntry_2DFX(pIDEFormat, bxa::_2DFX_PROC_OBJECT)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif