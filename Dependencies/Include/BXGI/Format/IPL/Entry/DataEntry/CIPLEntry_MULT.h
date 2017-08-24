#ifndef CIPLEntry_MULT_H
#define CIPLEntry_MULT_H

#include "bxgi.h"
#include "Type/Types.h"
#include "Format/IPL/Entry/CIPLEntry_Data.h"

class bxgi::CIPLEntry_MULT : public bxgi::CIPLEntry_Data
{
public:
	CIPLEntry_MULT(bxgi::CIPLFormat *pIPLFormat) :
		CIPLEntry_Data(pIPLFormat, IPL_SECTION_MULT)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif