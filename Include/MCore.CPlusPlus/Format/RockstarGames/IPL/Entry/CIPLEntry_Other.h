#ifndef CIPLEntry_Other_H
#define CIPLEntry_Other_H

#include "mcore.h"
#include "Format/RockstarGames/IPL/CIPLEntry.h"
#include "Format/RockstarGames/Helper/SectionLines/Entry/CSectionLinesEntry_Other.h"

class mcore::CIPLFormat;

class mcore::CIPLEntry_Other : public mcore::CSectionLinesEntry_Other, public mcore::CIPLEntry
{
public:
	CIPLEntry_Other(mcore::CIPLFormat *pIPLFormat) :
		CIPLEntry(pIPLFormat)
	{};

	void							unserialize(void);
	void							serialize(void);
};

#endif