#ifndef CIDEEntry_H
#define CIDEEntry_H

#include "bxcf.h"
#include "Type/Types.h"
#include "eIDESection.h"
#include "Format/RockstarGames/Helper/SectionLines/CSectionLinesEntry.h"
#include <string>
#include <vector>

class bxcf::CIDEFormat;

class bxcf::CIDEEntry : public bxcf::CSectionLinesEntry<CIDEFormat, eIDESection>
{
public:
	CIDEEntry(CIDEFormat *pIDEFormat);
};

#endif