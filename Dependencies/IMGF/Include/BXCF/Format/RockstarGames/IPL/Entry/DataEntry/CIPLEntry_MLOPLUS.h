#ifndef CIPLEntry_MLOPLUS_H
#define CIPLEntry_MLOPLUS_H

#include "bxcf.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IPL/Entry/CIPLEntry_Data.h"

class bxcf::CIPLEntry_MLOPLUS : public bxcf::CIPLEntry_Data
{
public:
	CIPLEntry_MLOPLUS(bxcf::CIPLFormat *pIPLFormat) :
		CIPLEntry_Data(pIPLFormat, IPL_SECTION_MLOPLUS)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif