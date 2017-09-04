#ifndef CIPLEntry_SLOW_H
#define CIPLEntry_SLOW_H

#include "bxcf.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IPL/Entry/CIPLEntry_Data.h"

class bxcf::CIPLEntry_SLOW : public bxcf::CIPLEntry_Data
{
public:
	CIPLEntry_SLOW(bxcf::CIPLFormat *pIPLFormat) :
		CIPLEntry_Data(pIPLFormat, IPL_SECTION_SLOW)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif