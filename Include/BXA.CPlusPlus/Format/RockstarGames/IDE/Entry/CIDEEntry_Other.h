#ifndef CIDEEntry_Other_H
#define CIDEEntry_Other_H

#include "BXA.h"
#include "Format/RockstarGames/IDE/CIDEEntry.h"
#include "Format/RockstarGames/Helper/SectionLines/Entry/CSectionLinesEntry_Other.h"

class bxa::CIDEFormat;

class bxa::CIDEEntry_Other : public bxa::CSectionLinesEntry_Other, public bxa::CIDEEntry
{
public:
	CIDEEntry_Other(bxa::CIDEFormat *pIDEFormat) :
		CIDEEntry(pIDEFormat)
	{};

	void							unserialize(void);
	void							serialize(void);
};

#endif