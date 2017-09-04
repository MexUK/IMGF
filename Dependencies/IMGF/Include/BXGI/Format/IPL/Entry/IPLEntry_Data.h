#pragma once

#include "nsbxgi.h"
#include "Format/IPL/IPLEntry.h"
#include "Helper/SectionLines/Entry/SectionLinesEntry_Data.h"

class bxgi::IPLEntry_Data : public bxgi::SectionLinesEntry_Data, public bxgi::IPLEntry
{
public:
	IPLEntry_Data(bxgi::IPLFormat *pIPLFormat, bxgi::EIPLSection EIPLSectionValue) :
		IPLEntry(pIPLFormat)
	{
		setSectionType(EIPLSectionValue);
	};
};