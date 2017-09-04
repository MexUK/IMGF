#pragma once

#include "nsbxgi.h"
#include "Format/IDE/IDEEntry.h"
#include "Helper/SectionLines/Entry/SectionLinesEntry_Other.h"

class bxgi::IDEFormat;

class bxgi::IDEEntry_Other : public bxgi::SectionLinesEntry_Other, public bxgi::IDEEntry
{
public:
	IDEEntry_Other(bxgi::IDEFormat *pIDEFormat);

	void							unserialize(void);
	void							serialize(void);
};