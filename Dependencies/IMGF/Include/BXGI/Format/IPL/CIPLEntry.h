#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "EIPLSection.h"
#include "Helper/SectionLines/CSectionLinesEntry.h"

class bxgi::CIPLFormat;

class bxgi::CIPLEntry : public bxgi::CSectionLinesEntry<CIPLFormat, EIPLSection>
{
public:
	CIPLEntry(bxgi::CIPLFormat *pIPLFormat);
};