#ifndef CIPLEntry_BLOK_H
#define CIPLEntry_BLOK_H

#include "mcore.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IPL/Entry/CIPLEntry_Data.h"

class mcore::CIPLEntry_BLOK : public mcore::CIPLEntry_Data
{
public:
	CIPLEntry_BLOK(mcore::CIPLFormat *pIPLFormat) :
		CIPLEntry_Data(pIPLFormat, IPL_SECTION_BLOK)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif