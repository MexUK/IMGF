#ifndef CIPLEntry_MLOPLUS_H
#define CIPLEntry_MLOPLUS_H

#include "bxgi.h"
#include "Type/Types.h"
#include "Format/IPL/Entry/CIPLEntry_Data.h"

class bxgi::CIPLEntry_MLOPLUS : public bxgi::CIPLEntry_Data
{
public:
	CIPLEntry_MLOPLUS(bxgi::CIPLFormat *pIPLFormat) :
		CIPLEntry_Data(pIPLFormat, IPL_SECTION_MLOPLUS)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif