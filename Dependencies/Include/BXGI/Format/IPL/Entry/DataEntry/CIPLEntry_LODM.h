#ifndef CIPLEntry_LODM_H
#define CIPLEntry_LODM_H

#include "bxgi.h"
#include "Type/Types.h"
#include "Format/IPL/Entry/CIPLEntry_Data.h"

class bxgi::CIPLEntry_LODM : public bxgi::CIPLEntry_Data
{
public:
	CIPLEntry_LODM(bxgi::CIPLFormat *pIPLFormat) :
		CIPLEntry_Data(pIPLFormat, IPL_SECTION_LODM)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif