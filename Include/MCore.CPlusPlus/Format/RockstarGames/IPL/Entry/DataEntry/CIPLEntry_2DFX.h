#ifndef CIPLEntry_2DFX_H
#define CIPLEntry_2DFX_H

#include "bxa.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IPL/Entry/CIPLEntry_Data.h"

class bxa::CIPLEntry_2DFX : public bxa::CIPLEntry_Data
{
public:
	CIPLEntry_2DFX(bxa::CIPLFormat *pIPLFormat) :
		CIPLEntry_Data(pIPLFormat, IPL_SECTION_2DFX)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif