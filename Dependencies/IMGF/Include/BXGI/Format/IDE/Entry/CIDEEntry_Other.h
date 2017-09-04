#pragma once

#include "nsbxgi.h"
#include "Format/IDE/CIDEEntry.h"
#include "Helper/SectionLines/Entry/CSectionLinesEntry_Other.h"

class bxgi::CIDEFormat;

class bxgi::CIDEEntry_Other : public bxgi::CSectionLinesEntry_Other, public bxgi::CIDEEntry
{
public:
	CIDEEntry_Other(bxgi::CIDEFormat *pIDEFormat);

	void							unserialize(void);
	void							serialize(void);
};