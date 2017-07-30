#ifndef CIPLEntry_LINK_H
#define CIPLEntry_LINK_H

#include "bxcf.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IPL/Entry/CIPLEntry_Data.h"

class bxcf::CIPLEntry_LINK : public bxcf::CIPLEntry_Data
{
public:
	CIPLEntry_LINK(bxcf::CIPLFormat *pIPLFormat) :
		CIPLEntry_Data(pIPLFormat, IPL_SECTION_LINK)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif