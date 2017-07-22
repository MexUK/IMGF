#ifndef CIPLEntry_LINK_H
#define CIPLEntry_LINK_H

#include "BXA.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IPL/Entry/CIPLEntry_Data.h"

class bxa::CIPLEntry_LINK : public bxa::CIPLEntry_Data
{
public:
	CIPLEntry_LINK(bxa::CIPLFormat *pIPLFormat) :
		CIPLEntry_Data(pIPLFormat, IPL_SECTION_LINK)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif