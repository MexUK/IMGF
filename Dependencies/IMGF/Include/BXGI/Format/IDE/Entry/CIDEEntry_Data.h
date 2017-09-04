#pragma once

#include "nsbxgi.h"
#include "Format/IDE/CIDEEntry.h"
#include "Helper/SectionLines/Entry/CSectionLinesEntry_Data.h"

class bxgi::CIDEEntry_Data : public bxgi::CSectionLinesEntry_Data, public bxgi::CIDEEntry
{
public:
	CIDEEntry_Data(bxgi::CIDEFormat *pIDEFormat, bxgi::EIDESection EIDESectionValue) :
		CIDEEntry(pIDEFormat)
	{
		setSectionType(EIDESectionValue);
	};
};