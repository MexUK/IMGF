#ifndef CIPLEntry_H
#define CIPLEntry_H

#include "bxcf.h"
#include "Type/Types.h"
#include "eIPLSection.h"
#include "Format/RockstarGames/Helper/SectionLines/CSectionLinesEntry.h"
#include <string>
#include <vector>

class bxcf::CIPLFormat;

class bxcf::CIPLEntry : public bxcf::CSectionLinesEntry<CIPLFormat, eIPLSection>
{
public:
	CIPLEntry(bxcf::CIPLFormat *pIPLFormat);
};

#endif