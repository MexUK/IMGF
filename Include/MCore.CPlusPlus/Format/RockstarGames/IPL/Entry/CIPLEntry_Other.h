#ifndef CIPLEntry_Other_H
#define CIPLEntry_Other_H

#include "bxa.h"
#include "Format/RockstarGames/IPL/CIPLEntry.h"
#include "Format/RockstarGames/Helper/SectionLines/Entry/CSectionLinesEntry_Other.h"

class bxa::CIPLFormat;

class bxa::CIPLEntry_Other : public bxa::CSectionLinesEntry_Other, public bxa::CIPLEntry
{
public:
	CIPLEntry_Other(bxa::CIPLFormat *pIPLFormat) :
		CIPLEntry(pIPLFormat)
	{};

	void							unserialize(void);
	void							serialize(void);
};

#endif