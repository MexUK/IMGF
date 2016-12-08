#ifndef CIPLEntry_Data_H
#define CIPLEntry_Data_H

#include "mcore.h"
#include "Format/RockstarGames/IPL/CIPLEntry.h"
#include "Format/RockstarGames/Helper/SectionLines/Entry/CSectionLinesEntry_Data.h"

class mcore::CIPLEntry_Data : public mcore::CSectionLinesEntry_Data, public mcore::CIPLEntry
{
public:
	CIPLEntry_Data(mcore::CIPLFormat *pIPLFormat, mcore::eIPLSection eIPLSectionValue) :
		CIPLEntry(pIPLFormat)
	{
		setSectionType(eIPLSectionValue);
	};
};

#endif