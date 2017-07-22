#ifndef CIPLEntry_RTFX_H
#define CIPLEntry_RTFX_H

#include "bxa.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IPL/Entry/CIPLEntry_Data.h"

class bxa::CIPLEntry_RTFX : public bxa::CIPLEntry_Data
{
public:
	CIPLEntry_RTFX(bxa::CIPLFormat *pIPLFormat) :
		CIPLEntry_Data(pIPLFormat, IPL_SECTION_RTFX)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif