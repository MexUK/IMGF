#pragma once

#include "nsbxgi.h"
#include "Format/IDE/IDEEntry.h"
#include "Helper/SectionLines/Entry/SectionLinesEntry_Data.h"

class bxgi::IDEEntry_Data : public bxgi::SectionLinesEntry_Data, public bxgi::IDEEntry
{
public:
	IDEEntry_Data(bxgi::IDEFormat *pIDEFormat, bxgi::EIDESection EIDESectionValue) :
		IDEEntry(pIDEFormat)
	{
		setSectionType(EIDESectionValue);
	};
};