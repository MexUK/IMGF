#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "EIPLSection.h"
#include "Helper/SectionLines/SectionLinesEntry.h"

class bxgi::IPLFormat;

class bxgi::IPLEntry : public bxgi::SectionLinesEntry<IPLFormat, EIPLSection>
{
public:
	IPLEntry(bxgi::IPLFormat *pIPLFormat);
};