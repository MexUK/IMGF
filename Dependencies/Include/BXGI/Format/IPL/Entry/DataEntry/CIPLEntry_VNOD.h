#ifndef CIPLEntry_VNOD_H
#define CIPLEntry_VNOD_H

#include "bxgi.h"
#include "Type/Types.h"
#include "Format/IPL/Entry/CIPLEntry_Data.h"

class bxgi::CIPLEntry_VNOD : public bxgi::CIPLEntry_Data
{
public:
	CIPLEntry_VNOD(bxgi::CIPLFormat *pIPLFormat) :
		CIPLEntry_Data(pIPLFormat, IPL_SECTION_VNOD)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif