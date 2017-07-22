#ifndef CIPLEntry_MLOPLUS_H
#define CIPLEntry_MLOPLUS_H

#include "bxa.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IPL/Entry/CIPLEntry_Data.h"

class bxa::CIPLEntry_MLOPLUS : public bxa::CIPLEntry_Data
{
public:
	CIPLEntry_MLOPLUS(bxa::CIPLFormat *pIPLFormat) :
		CIPLEntry_Data(pIPLFormat, IPL_SECTION_MLOPLUS)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif