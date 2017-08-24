#ifndef CIDEEntry_Other_H
#define CIDEEntry_Other_H

#include "bxgi.h"
#include "Format/IDE/CIDEEntry.h"
#include "Helper/SectionLines/Entry/CSectionLinesEntry_Other.h"

class bxgi::CIDEFormat;

class bxgi::CIDEEntry_Other : public bxgi::CSectionLinesEntry_Other, public bxgi::CIDEEntry
{
public:
	CIDEEntry_Other(bxgi::CIDEFormat *pIDEFormat) :
		CIDEEntry(pIDEFormat)
	{};

	void							unserialize(void);
	void							serialize(void);
};

#endif