#pragma once

#include "nsbxgi.h"
#include "Format/IPL/IPLEntry.h"

class bxgi::IPLFormat;

class bxgi::IPLEntry_Section : public bxgi::IPLEntry
{
public:
	IPLEntry_Section(bxgi::IPLFormat *pIPLFormat);

	void					unserialize(void);
	void					serialize(void);
};