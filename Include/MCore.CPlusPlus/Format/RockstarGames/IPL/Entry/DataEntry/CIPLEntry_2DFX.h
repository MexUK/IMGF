#ifndef CIPLEntry_2DFX_H
#define CIPLEntry_2DFX_H

#include "mcore.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IPL/Entry/CIPLEntry_Data.h"

class mcore::CIPLEntry_2DFX : public mcore::CIPLEntry_Data
{
public:
	CIPLEntry_2DFX(mcore::CIPLFormat *pIPLFormat) :
		CIPLEntry_Data(pIPLFormat, IPL_SECTION_2DFX)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif