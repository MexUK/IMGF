#ifndef CIPLEntry_VNOD_H
#define CIPLEntry_VNOD_H

#include "mcore.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IPL/Entry/CIPLEntry_Data.h"

class mcore::CIPLEntry_VNOD : public mcore::CIPLEntry_Data
{
public:
	CIPLEntry_VNOD(mcore::CIPLFormat *pIPLFormat) :
		CIPLEntry_Data(pIPLFormat, IPL_SECTION_VNOD)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif