#ifndef CIPLEntry_Data_H
#define CIPLEntry_Data_H

#include "bxgi.h"
#include "Format/IPL/CIPLEntry.h"
#include "Helper/SectionLines/Entry/CSectionLinesEntry_Data.h"

class bxgi::CIPLEntry_Data : public bxgi::CSectionLinesEntry_Data, public bxgi::CIPLEntry
{
public:
	CIPLEntry_Data(bxgi::CIPLFormat *pIPLFormat, bxgi::eIPLSection eIPLSectionValue) :
		CIPLEntry(pIPLFormat)
	{
		setSectionType(eIPLSectionValue);
	};
};

#endif