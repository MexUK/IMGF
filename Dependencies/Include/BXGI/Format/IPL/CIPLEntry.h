#ifndef CIPLEntry_H
#define CIPLEntry_H

#include "bxgi.h"
#include "Type/Types.h"
#include "eIPLSection.h"
#include "Helper/SectionLines/CSectionLinesEntry.h"

class bxgi::CIPLFormat;

class bxgi::CIPLEntry : public bxgi::CSectionLinesEntry<CIPLFormat, eIPLSection>
{
public:
	CIPLEntry(bxgi::CIPLFormat *pIPLFormat);
};

#endif