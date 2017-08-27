#pragma once

#include "nsbxgi.h"
#include "Format/IPL/CIPLEntry.h"

class bxgi::CIPLFormat;

class bxgi::CIPLEntry_Section : public bxgi::CIPLEntry
{
public:
	CIPLEntry_Section(bxgi::CIPLFormat *pIPLFormat);

	void					unserialize(void);
	void					serialize(void);
};