#ifndef CIPLEntry_Data_H
#define CIPLEntry_Data_H

#include "bxcf.h"
#include "Format/RockstarGames/IPL/CIPLEntry.h"
#include "Format/RockstarGames/Helper/SectionLines/Entry/CSectionLinesEntry_Data.h"

class bxcf::CIPLEntry_Data : public bxcf::CSectionLinesEntry_Data, public bxcf::CIPLEntry
{
public:
	CIPLEntry_Data(bxcf::CIPLFormat *pIPLFormat, bxcf::eIPLSection eIPLSectionValue) :
		CIPLEntry(pIPLFormat)
	{
		setSectionType(eIPLSectionValue);
	};
};

#endif