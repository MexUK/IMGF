#ifndef CIDEEntry_Data_H
#define CIDEEntry_Data_H

#include "bxgi.h"
#include "Format/IDE/CIDEEntry.h"
#include "Helper/SectionLines/Entry/CSectionLinesEntry_Data.h"

class bxgi::CIDEEntry_Data : public bxgi::CSectionLinesEntry_Data, public bxgi::CIDEEntry
{
public:
	CIDEEntry_Data(bxgi::CIDEFormat *pIDEFormat, bxgi::eIDESection eIDESectionValue) :
		CIDEEntry(pIDEFormat)
	{
		setSectionType(eIDESectionValue);
	};
};

#endif