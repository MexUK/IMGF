#ifndef CIPLEntry_LODM_H
#define CIPLEntry_LODM_H

#include "mcore.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IPL/Entry/CIPLEntry_Data.h"

class mcore::CIPLEntry_LODM : public mcore::CIPLEntry_Data
{
public:
	CIPLEntry_LODM(mcore::CIPLFormat *pIPLFormat) :
		CIPLEntry_Data(pIPLFormat, IPL_SECTION_LODM)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif