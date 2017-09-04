#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "Format/IPL/Entry/IPLEntry_Data.h"

class bxgi::IPLEntry_MULT : public bxgi::IPLEntry_Data
{
public:
	IPLEntry_MULT(bxgi::IPLFormat *pIPLFormat);

	void						unserialize(void);
	void						serialize(void);
};