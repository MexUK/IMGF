#ifndef CIPLEntry_RTFX_H
#define CIPLEntry_RTFX_H

#include "bxcf.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IPL/Entry/CIPLEntry_Data.h"

class bxcf::CIPLEntry_RTFX : public bxcf::CIPLEntry_Data
{
public:
	CIPLEntry_RTFX(bxcf::CIPLFormat *pIPLFormat) :
		CIPLEntry_Data(pIPLFormat, IPL_SECTION_RTFX)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif