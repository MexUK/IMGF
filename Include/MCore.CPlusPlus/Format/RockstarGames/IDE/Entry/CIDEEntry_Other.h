#ifndef CIDEEntry_Other_H
#define CIDEEntry_Other_H

#include "mcore.h"
#include "Format/RockstarGames/IDE/CIDEEntry.h"
#include "Format/RockstarGames/Helper/SectionLines/Entry/CSectionLinesEntry_Other.h"

class mcore::CIDEFormat;

class mcore::CIDEEntry_Other : public mcore::CSectionLinesEntry_Other, public mcore::CIDEEntry
{
public:
	CIDEEntry_Other(mcore::CIDEFormat *pIDEFormat) :
		CIDEEntry(pIDEFormat)
	{};

	void							unserialize(void);
	void							serialize(void);
};

#endif