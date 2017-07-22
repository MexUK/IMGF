#ifndef CIPLEntry_BLOK_H
#define CIPLEntry_BLOK_H

#include "bxa.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IPL/Entry/CIPLEntry_Data.h"

class bxa::CIPLEntry_BLOK : public bxa::CIPLEntry_Data
{
public:
	CIPLEntry_BLOK(bxa::CIPLFormat *pIPLFormat) :
		CIPLEntry_Data(pIPLFormat, IPL_SECTION_BLOK)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif