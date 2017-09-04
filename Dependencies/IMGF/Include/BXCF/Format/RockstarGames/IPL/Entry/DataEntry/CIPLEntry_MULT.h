#ifndef CIPLEntry_MULT_H
#define CIPLEntry_MULT_H

#include "bxcf.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IPL/Entry/CIPLEntry_Data.h"

class bxcf::CIPLEntry_MULT : public bxcf::CIPLEntry_Data
{
public:
	CIPLEntry_MULT(bxcf::CIPLFormat *pIPLFormat) :
		CIPLEntry_Data(pIPLFormat, IPL_SECTION_MULT)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif