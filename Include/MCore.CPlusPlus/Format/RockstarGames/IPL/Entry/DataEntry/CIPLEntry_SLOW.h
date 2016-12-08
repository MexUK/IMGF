#ifndef CIPLEntry_SLOW_H
#define CIPLEntry_SLOW_H

#include "mcore.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IPL/Entry/CIPLEntry_Data.h"

class mcore::CIPLEntry_SLOW : public mcore::CIPLEntry_Data
{
public:
	CIPLEntry_SLOW(mcore::CIPLFormat *pIPLFormat) :
		CIPLEntry_Data(pIPLFormat, IPL_SECTION_SLOW)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif