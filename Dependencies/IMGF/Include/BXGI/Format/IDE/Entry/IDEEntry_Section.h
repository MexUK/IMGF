#pragma once

#include "nsbxgi.h"
#include "Format/IDE/IDEEntry.h"

class bxgi::IDEFormat;

class bxgi::IDEEntry_Section : public bxgi::IDEEntry
{
public:
	IDEEntry_Section(bxgi::IDEFormat *pIDEFormat);

	void					unserialize(void);
	void					serialize(void);
};