#ifndef CIPLEntry_MLOPLUS_H
#define CIPLEntry_MLOPLUS_H

#include "mcore.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IPL/Entry/CIPLEntry_Data.h"

class mcore::CIPLEntry_MLOPLUS : public mcore::CIPLEntry_Data
{
public:
	CIPLEntry_MLOPLUS(mcore::CIPLFormat *pIPLFormat) :
		CIPLEntry_Data(pIPLFormat, IPL_SECTION_MLOPLUS)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif