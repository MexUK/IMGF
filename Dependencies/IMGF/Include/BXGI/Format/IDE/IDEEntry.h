#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "EIDESection.h"
#include "Helper/SectionLines/SectionLinesEntry.h"

class bxgi::IDEFormat;

class bxgi::IDEEntry : public bxgi::SectionLinesEntry<IDEFormat, EIDESection>
{
public:
	IDEEntry(IDEFormat *pIDEFormat);
};