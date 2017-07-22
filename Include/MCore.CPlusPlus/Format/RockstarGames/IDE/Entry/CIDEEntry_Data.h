#ifndef CIDEEntry_Data_H
#define CIDEEntry_Data_H

#include "bxa.h"
#include "Format/RockstarGames/IDE/CIDEEntry.h"
#include "Format/RockstarGames/Helper/SectionLines/Entry/CSectionLinesEntry_Data.h"

class bxa::CIDEEntry_Data : public bxa::CSectionLinesEntry_Data, public bxa::CIDEEntry
{
public:
	CIDEEntry_Data(bxa::CIDEFormat *pIDEFormat, bxa::eIDESection eIDESectionValue) :
		CIDEEntry(pIDEFormat)
	{
		setSectionType(eIDESectionValue);
	};
};

#endif