#ifndef CIPLEntry_Data_H
#define CIPLEntry_Data_H

#include "BXA.h"
#include "Format/RockstarGames/IPL/CIPLEntry.h"
#include "Format/RockstarGames/Helper/SectionLines/Entry/CSectionLinesEntry_Data.h"

class bxa::CIPLEntry_Data : public bxa::CSectionLinesEntry_Data, public bxa::CIPLEntry
{
public:
	CIPLEntry_Data(bxa::CIPLFormat *pIPLFormat, bxa::eIPLSection eIPLSectionValue) :
		CIPLEntry(pIPLFormat)
	{
		setSectionType(eIPLSectionValue);
	};
};

#endif