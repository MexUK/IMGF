#ifndef CIDEEntry_2DFX_ProcObject_H
#define CIDEEntry_2DFX_ProcObject_H

#include "mcore.h"
#include "Format/RockstarGames/IDE/Entry/DataEntry/CIDEEntry_2DFX.h"
#include <string>

class mcore::CIDEEntry_2DFX_ProcObject : public mcore::CIDEEntry_2DFX
{
public:
	CIDEEntry_2DFX_ProcObject(mcore::CIDEFormat *pIDEFormat) :
		CIDEEntry_2DFX(pIDEFormat, mcore::_2DFX_PROC_OBJECT)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif