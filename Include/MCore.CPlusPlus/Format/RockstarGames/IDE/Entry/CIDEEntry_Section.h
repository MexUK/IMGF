#ifndef CIDEEntry_Section_H
#define CIDEEntry_Section_H

#include "bxa.h"
#include "Format/RockstarGames/IDE/CIDEEntry.h"

class bxa::CIDEFormat;

class bxa::CIDEEntry_Section : public bxa::CIDEEntry
{
public:
	CIDEEntry_Section(bxa::CIDEFormat *pIDEFormat) :
		CIDEEntry(pIDEFormat)
	{};

	void					unserialize(void);
	void					serialize(void);
};

#endif