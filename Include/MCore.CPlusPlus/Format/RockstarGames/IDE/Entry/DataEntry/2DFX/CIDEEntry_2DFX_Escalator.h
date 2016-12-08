#ifndef CIDEEntry_2DFX_Escalator_H
#define CIDEEntry_2DFX_Escalator_H

#include "mcore.h"
#include "Format/RockstarGames/IDE/Entry/DataEntry/CIDEEntry_2DFX.h"
#include <string>

class mcore::CIDEEntry_2DFX_Escalator : public mcore::CIDEEntry_2DFX
{
public:
	CIDEEntry_2DFX_Escalator(mcore::CIDEFormat *pIDEFormat) :
		CIDEEntry_2DFX(pIDEFormat, mcore::_2DFX_ESCALATOR)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif