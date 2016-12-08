#ifndef CIDEEntry_Section_H
#define CIDEEntry_Section_H

#include "mcore.h"
#include "Format/RockstarGames/IDE/CIDEEntry.h"

class mcore::CIDEFormat;

class mcore::CIDEEntry_Section : public mcore::CIDEEntry
{
public:
	CIDEEntry_Section(mcore::CIDEFormat *pIDEFormat) :
		CIDEEntry(pIDEFormat)
	{};

	void					unserialize(void);
	void					serialize(void);
};

#endif