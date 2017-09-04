#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "Format/IPL/Entry/CIPLEntry_Data.h"

class bxgi::CIPLEntry_MLOPLUS : public bxgi::CIPLEntry_Data
{
public:
	CIPLEntry_MLOPLUS(bxgi::CIPLFormat *pIPLFormat);

	void						unserialize(void);
	void						serialize(void);
};