#ifndef CIPLEntry_SLOW_H
#define CIPLEntry_SLOW_H

#include "BXA.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IPL/Entry/CIPLEntry_Data.h"

class bxa::CIPLEntry_SLOW : public bxa::CIPLEntry_Data
{
public:
	CIPLEntry_SLOW(bxa::CIPLFormat *pIPLFormat) :
		CIPLEntry_Data(pIPLFormat, IPL_SECTION_SLOW)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif