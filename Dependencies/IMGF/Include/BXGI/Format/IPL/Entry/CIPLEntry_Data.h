#pragma once

#include "nsbxgi.h"
#include "Format/IPL/CIPLEntry.h"
#include "Helper/SectionLines/Entry/CSectionLinesEntry_Data.h"

class bxgi::CIPLEntry_Data : public bxgi::CSectionLinesEntry_Data, public bxgi::CIPLEntry
{
public:
	CIPLEntry_Data(bxgi::CIPLFormat *pIPLFormat, bxgi::EIPLSection EIPLSectionValue) :
		CIPLEntry(pIPLFormat)
	{
		setSectionType(EIPLSectionValue);
	};
};