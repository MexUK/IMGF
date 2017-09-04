#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "EIDESection.h"
#include "Helper/SectionLines/CSectionLinesEntry.h"

class bxgi::CIDEFormat;

class bxgi::CIDEEntry : public bxgi::CSectionLinesEntry<CIDEFormat, EIDESection>
{
public:
	CIDEEntry(CIDEFormat *pIDEFormat);
};