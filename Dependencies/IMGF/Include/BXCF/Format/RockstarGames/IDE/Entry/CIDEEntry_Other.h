#ifndef CIDEEntry_Other_H
#define CIDEEntry_Other_H

#include "bxcf.h"
#include "Format/RockstarGames/IDE/CIDEEntry.h"
#include "Format/RockstarGames/Helper/SectionLines/Entry/CSectionLinesEntry_Other.h"

class bxcf::CIDEFormat;

class bxcf::CIDEEntry_Other : public bxcf::CSectionLinesEntry_Other, public bxcf::CIDEEntry
{
public:
	CIDEEntry_Other(bxcf::CIDEFormat *pIDEFormat) :
		CIDEEntry(pIDEFormat)
	{};

	void							unserialize(void);
	void							serialize(void);
};

#endif