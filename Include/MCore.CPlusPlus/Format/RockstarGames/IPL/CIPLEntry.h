#ifndef CIPLEntry_H
#define CIPLEntry_H

#include "mcore.h"
#include "Type/Types.h"
#include "eIPLSection.h"
#include "Format/RockstarGames/Helper/SectionLines/CSectionLinesEntry.h"
#include <string>
#include <vector>

class mcore::CIPLFormat;

class mcore::CIPLEntry : public mcore::CSectionLinesEntry<CIPLFormat, eIPLSection>
{
public:
	CIPLEntry(mcore::CIPLFormat *pIPLFormat);
};

#endif