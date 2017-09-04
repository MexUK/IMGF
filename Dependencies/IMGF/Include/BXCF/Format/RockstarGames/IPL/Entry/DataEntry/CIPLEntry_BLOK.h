#ifndef CIPLEntry_BLOK_H
#define CIPLEntry_BLOK_H

#include "bxcf.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IPL/Entry/CIPLEntry_Data.h"

class bxcf::CIPLEntry_BLOK : public bxcf::CIPLEntry_Data
{
public:
	CIPLEntry_BLOK(bxcf::CIPLFormat *pIPLFormat) :
		CIPLEntry_Data(pIPLFormat, IPL_SECTION_BLOK)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif