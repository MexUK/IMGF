#ifndef CIPLEntry_2DFX_H
#define CIPLEntry_2DFX_H

#include "bxgi.h"
#include "Type/Types.h"
#include "Format/IPL/Entry/CIPLEntry_Data.h"

class bxgi::CIPLEntry_2DFX : public bxgi::CIPLEntry_Data
{
public:
	CIPLEntry_2DFX(bxgi::CIPLFormat *pIPLFormat) :
		CIPLEntry_Data(pIPLFormat, IPL_SECTION_2DFX)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif