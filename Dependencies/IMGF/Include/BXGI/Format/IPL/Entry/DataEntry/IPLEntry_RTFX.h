#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "Format/IPL/Entry/IPLEntry_Data.h"

class bxgi::IPLEntry_RTFX : public bxgi::IPLEntry_Data
{
public:
	IPLEntry_RTFX(bxgi::IPLFormat *pIPLFormat);

	void						unserialize(void);
	void						serialize(void);
};