#ifndef CIPLEntry_MULT_H
#define CIPLEntry_MULT_H

#include "mcore.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IPL/Entry/CIPLEntry_Data.h"

class mcore::CIPLEntry_MULT : public mcore::CIPLEntry_Data
{
public:
	CIPLEntry_MULT(mcore::CIPLFormat *pIPLFormat) :
		CIPLEntry_Data(pIPLFormat, IPL_SECTION_MULT)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif