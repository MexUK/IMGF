#ifndef CIPLEntry_SLOW_H
#define CIPLEntry_SLOW_H

#include "bxgi.h"
#include "Type/Types.h"
#include "Format/IPL/Entry/CIPLEntry_Data.h"

class bxgi::CIPLEntry_SLOW : public bxgi::CIPLEntry_Data
{
public:
	CIPLEntry_SLOW(bxgi::CIPLFormat *pIPLFormat) :
		CIPLEntry_Data(pIPLFormat, IPL_SECTION_SLOW)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif