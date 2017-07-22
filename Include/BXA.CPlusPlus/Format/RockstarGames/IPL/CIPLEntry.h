#ifndef CIPLEntry_H
#define CIPLEntry_H

#include "BXA.h"
#include "Type/Types.h"
#include "eIPLSection.h"
#include "Format/RockstarGames/Helper/SectionLines/CSectionLinesEntry.h"
#include <string>
#include <vector>

class bxa::CIPLFormat;

class bxa::CIPLEntry : public bxa::CSectionLinesEntry<CIPLFormat, eIPLSection>
{
public:
	CIPLEntry(bxa::CIPLFormat *pIPLFormat);
};

#endif