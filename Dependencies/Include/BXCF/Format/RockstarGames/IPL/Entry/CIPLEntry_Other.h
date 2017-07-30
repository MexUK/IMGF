#ifndef CIPLEntry_Other_H
#define CIPLEntry_Other_H

#include "bxcf.h"
#include "Format/RockstarGames/IPL/CIPLEntry.h"
#include "Format/RockstarGames/Helper/SectionLines/Entry/CSectionLinesEntry_Other.h"

class bxcf::CIPLFormat;

class bxcf::CIPLEntry_Other : public bxcf::CSectionLinesEntry_Other, public bxcf::CIPLEntry
{
public:
	CIPLEntry_Other(bxcf::CIPLFormat *pIPLFormat) :
		CIPLEntry(pIPLFormat)
	{};

	void							unserialize(void);
	void							serialize(void);
};

#endif