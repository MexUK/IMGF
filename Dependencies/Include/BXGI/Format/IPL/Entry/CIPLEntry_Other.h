#ifndef CIPLEntry_Other_H
#define CIPLEntry_Other_H

#include "bxgi.h"
#include "Format/IPL/CIPLEntry.h"
#include "Helper/SectionLines/Entry/CSectionLinesEntry_Other.h"

class bxgi::CIPLFormat;

class bxgi::CIPLEntry_Other : public bxgi::CSectionLinesEntry_Other, public bxgi::CIPLEntry
{
public:
	CIPLEntry_Other(bxgi::CIPLFormat *pIPLFormat) :
		CIPLEntry(pIPLFormat)
	{};

	void							unserialize(void);
	void							serialize(void);
};

#endif