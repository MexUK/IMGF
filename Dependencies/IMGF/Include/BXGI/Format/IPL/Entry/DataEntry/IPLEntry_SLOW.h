#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "Format/IPL/Entry/IPLEntry_Data.h"

class bxgi::IPLEntry_SLOW : public bxgi::IPLEntry_Data
{
public:
	IPLEntry_SLOW(bxgi::IPLFormat *pIPLFormat);

	void						unserialize(void);
	void						serialize(void);
};