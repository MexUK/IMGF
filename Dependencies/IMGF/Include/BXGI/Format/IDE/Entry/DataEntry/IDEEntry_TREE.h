#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "Format/IDE/Entry/IDEEntry_Data.h"

class bxgi::IDEEntry_TREE : public bxgi::IDEEntry_Data
{
public:
	IDEEntry_TREE(bxgi::IDEFormat *pIDEFormat);

	void						unserialize(void);
	void						serialize(void);
};