#ifndef CIPLEntry_RTFX_H
#define CIPLEntry_RTFX_H

#include "bxgi.h"
#include "Type/Types.h"
#include "Format/IPL/Entry/CIPLEntry_Data.h"

class bxgi::CIPLEntry_RTFX : public bxgi::CIPLEntry_Data
{
public:
	CIPLEntry_RTFX(bxgi::CIPLFormat *pIPLFormat) :
		CIPLEntry_Data(pIPLFormat, IPL_SECTION_RTFX)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif