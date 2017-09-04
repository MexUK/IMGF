#ifndef CIPLEntry_2DFX_H
#define CIPLEntry_2DFX_H

#include "bxcf.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IPL/Entry/CIPLEntry_Data.h"

class bxcf::CIPLEntry_2DFX : public bxcf::CIPLEntry_Data
{
public:
	CIPLEntry_2DFX(bxcf::CIPLFormat *pIPLFormat) :
		CIPLEntry_Data(pIPLFormat, IPL_SECTION_2DFX)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif