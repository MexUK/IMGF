#ifndef CIDEEntry_Data_H
#define CIDEEntry_Data_H

#include "mcore.h"
#include "Format/RockstarGames/IDE/CIDEEntry.h"
#include "Format/RockstarGames/Helper/SectionLines/Entry/CSectionLinesEntry_Data.h"

class mcore::CIDEEntry_Data : public mcore::CSectionLinesEntry_Data, public mcore::CIDEEntry
{
public:
	CIDEEntry_Data(mcore::CIDEFormat *pIDEFormat, mcore::eIDESection eIDESectionValue) :
		CIDEEntry(pIDEFormat)
	{
		setSectionType(eIDESectionValue);
	};
};

#endif