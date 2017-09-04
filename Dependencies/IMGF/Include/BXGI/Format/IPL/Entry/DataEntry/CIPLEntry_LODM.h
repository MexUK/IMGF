#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "Format/IPL/Entry/CIPLEntry_Data.h"

class bxgi::CIPLEntry_LODM : public bxgi::CIPLEntry_Data
{
public:
	CIPLEntry_LODM(bxgi::CIPLFormat *pIPLFormat);

	void						unserialize(void);
	void						serialize(void);
};