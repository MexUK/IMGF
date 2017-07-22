#ifndef CIDEEntry_H
#define CIDEEntry_H

#include "BXA.h"
#include "Type/Types.h"
#include "eIDESection.h"
#include "Format/RockstarGames/Helper/SectionLines/CSectionLinesEntry.h"
#include <string>
#include <vector>

class bxa::CIDEFormat;

class bxa::CIDEEntry : public bxa::CSectionLinesEntry<CIDEFormat, eIDESection>
{
public:
	CIDEEntry(CIDEFormat *pIDEFormat);
};

#endif