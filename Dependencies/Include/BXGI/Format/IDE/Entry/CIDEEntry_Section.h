#pragma once

#include "nsbxgi.h"
#include "Format/IDE/CIDEEntry.h"

class bxgi::CIDEFormat;

class bxgi::CIDEEntry_Section : public bxgi::CIDEEntry
{
public:
	CIDEEntry_Section(bxgi::CIDEFormat *pIDEFormat);

	void					unserialize(void);
	void					serialize(void);
};