#pragma once

#include "nsbxgi.h"
#include "Format/IPL/IPLEntry.h"
#include "Helper/SectionLines/Entry/SectionLinesEntry_Other.h"

class bxgi::IPLFormat;

class bxgi::IPLEntry_Other : public bxgi::SectionLinesEntry_Other, public bxgi::IPLEntry
{
public:
	IPLEntry_Other(bxgi::IPLFormat *pIPLFormat);

	void							unserialize(void);
	void							serialize(void);
};