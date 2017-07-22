#ifndef CIPLEntry_VNOD_H
#define CIPLEntry_VNOD_H

#include "bxa.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IPL/Entry/CIPLEntry_Data.h"

class bxa::CIPLEntry_VNOD : public bxa::CIPLEntry_Data
{
public:
	CIPLEntry_VNOD(bxa::CIPLFormat *pIPLFormat) :
		CIPLEntry_Data(pIPLFormat, IPL_SECTION_VNOD)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif