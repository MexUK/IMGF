#ifndef CIDEEntry_Data_H
#define CIDEEntry_Data_H

#include "bxcf.h"
#include "Format/RockstarGames/IDE/CIDEEntry.h"
#include "Format/RockstarGames/Helper/SectionLines/Entry/CSectionLinesEntry_Data.h"

class bxcf::CIDEEntry_Data : public bxcf::CSectionLinesEntry_Data, public bxcf::CIDEEntry
{
public:
	CIDEEntry_Data(bxcf::CIDEFormat *pIDEFormat, bxcf::eIDESection eIDESectionValue) :
		CIDEEntry(pIDEFormat)
	{
		setSectionType(eIDESectionValue);
	};
};

#endif