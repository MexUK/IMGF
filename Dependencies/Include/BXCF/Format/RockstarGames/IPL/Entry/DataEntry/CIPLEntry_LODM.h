#ifndef CIPLEntry_LODM_H
#define CIPLEntry_LODM_H

#include "bxcf.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IPL/Entry/CIPLEntry_Data.h"

class bxcf::CIPLEntry_LODM : public bxcf::CIPLEntry_Data
{
public:
	CIPLEntry_LODM(bxcf::CIPLFormat *pIPLFormat) :
		CIPLEntry_Data(pIPLFormat, IPL_SECTION_LODM)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif