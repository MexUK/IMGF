#ifndef CIDEEntry_H
#define CIDEEntry_H

#include "mcore.h"
#include "Type/Types.h"
#include "eIDESection.h"
#include "Format/RockstarGames/Helper/SectionLines/CSectionLinesEntry.h"
#include <string>
#include <vector>

class mcore::CIDEFormat;

class mcore::CIDEEntry : public mcore::CSectionLinesEntry<CIDEFormat, eIDESection>
{
public:
	CIDEEntry(CIDEFormat *pIDEFormat);
};

#endif