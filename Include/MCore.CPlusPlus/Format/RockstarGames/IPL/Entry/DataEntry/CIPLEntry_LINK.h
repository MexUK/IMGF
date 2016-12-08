#ifndef CIPLEntry_LINK_H
#define CIPLEntry_LINK_H

#include "mcore.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IPL/Entry/CIPLEntry_Data.h"

class mcore::CIPLEntry_LINK : public mcore::CIPLEntry_Data
{
public:
	CIPLEntry_LINK(mcore::CIPLFormat *pIPLFormat) :
		CIPLEntry_Data(pIPLFormat, IPL_SECTION_LINK)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif