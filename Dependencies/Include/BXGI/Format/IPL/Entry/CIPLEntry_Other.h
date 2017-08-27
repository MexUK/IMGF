#pragma once

#include "nsbxgi.h"
#include "Format/IPL/CIPLEntry.h"
#include "Helper/SectionLines/Entry/CSectionLinesEntry_Other.h"

class bxgi::CIPLFormat;

class bxgi::CIPLEntry_Other : public bxgi::CSectionLinesEntry_Other, public bxgi::CIPLEntry
{
public:
	CIPLEntry_Other(bxgi::CIPLFormat *pIPLFormat);

	void							unserialize(void);
	void							serialize(void);
};