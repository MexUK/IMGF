#ifndef CIPLEntry_LODM_H
#define CIPLEntry_LODM_H

#include "BXA.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IPL/Entry/CIPLEntry_Data.h"

class bxa::CIPLEntry_LODM : public bxa::CIPLEntry_Data
{
public:
	CIPLEntry_LODM(bxa::CIPLFormat *pIPLFormat) :
		CIPLEntry_Data(pIPLFormat, IPL_SECTION_LODM)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif