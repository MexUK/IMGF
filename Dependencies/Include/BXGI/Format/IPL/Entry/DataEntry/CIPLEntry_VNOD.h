#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "Format/IPL/Entry/CIPLEntry_Data.h"

class bxgi::CIPLEntry_VNOD : public bxgi::CIPLEntry_Data
{
public:
	CIPLEntry_VNOD(bxgi::CIPLFormat *pIPLFormat);

	void						unserialize(void);
	void						serialize(void);
};