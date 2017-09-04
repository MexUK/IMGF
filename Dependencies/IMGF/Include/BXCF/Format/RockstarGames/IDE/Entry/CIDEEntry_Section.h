#ifndef CIDEEntry_Section_H
#define CIDEEntry_Section_H

#include "bxcf.h"
#include "Format/RockstarGames/IDE/CIDEEntry.h"

class bxcf::CIDEFormat;

class bxcf::CIDEEntry_Section : public bxcf::CIDEEntry
{
public:
	CIDEEntry_Section(bxcf::CIDEFormat *pIDEFormat) :
		CIDEEntry(pIDEFormat)
	{};

	void					unserialize(void);
	void					serialize(void);
};

#endif