#ifndef CIPLEntry_MULT_H
#define CIPLEntry_MULT_H

#include "bxa.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IPL/Entry/CIPLEntry_Data.h"

class bxa::CIPLEntry_MULT : public bxa::CIPLEntry_Data
{
public:
	CIPLEntry_MULT(bxa::CIPLFormat *pIPLFormat) :
		CIPLEntry_Data(pIPLFormat, IPL_SECTION_MULT)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif