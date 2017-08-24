#ifndef CIDEEntry_Section_H
#define CIDEEntry_Section_H

#include "bxgi.h"
#include "Format/IDE/CIDEEntry.h"

class bxgi::CIDEFormat;

class bxgi::CIDEEntry_Section : public bxgi::CIDEEntry
{
public:
	CIDEEntry_Section(bxgi::CIDEFormat *pIDEFormat) :
		CIDEEntry(pIDEFormat)
	{};

	void					unserialize(void);
	void					serialize(void);
};

#endif