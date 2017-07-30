#ifndef CIPLEntry_VNOD_H
#define CIPLEntry_VNOD_H

#include "bxcf.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IPL/Entry/CIPLEntry_Data.h"

class bxcf::CIPLEntry_VNOD : public bxcf::CIPLEntry_Data
{
public:
	CIPLEntry_VNOD(bxcf::CIPLFormat *pIPLFormat) :
		CIPLEntry_Data(pIPLFormat, IPL_SECTION_VNOD)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif