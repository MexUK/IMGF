#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "Format/IPL/Entry/CIPLEntry_Data.h"

class bxgi::CIPLEntry_SLOW : public bxgi::CIPLEntry_Data
{
public:
	CIPLEntry_SLOW(bxgi::CIPLFormat *pIPLFormat);

	void						unserialize(void);
	void						serialize(void);
};