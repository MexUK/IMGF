#ifndef CIPLEntry_RTFX_H
#define CIPLEntry_RTFX_H

#include "mcore.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IPL/Entry/CIPLEntry_Data.h"

class mcore::CIPLEntry_RTFX : public mcore::CIPLEntry_Data
{
public:
	CIPLEntry_RTFX(mcore::CIPLFormat *pIPLFormat) :
		CIPLEntry_Data(pIPLFormat, IPL_SECTION_RTFX)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif