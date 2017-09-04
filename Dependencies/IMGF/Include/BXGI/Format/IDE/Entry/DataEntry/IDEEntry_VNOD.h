#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "Format/IDE/Entry/IDEEntry_Data.h"

class bxgi::IDEEntry_VNOD : public bxgi::IDEEntry_Data
{
public:
	IDEEntry_VNOD(bxgi::IDEFormat *pIDEFormat);

	void						unserialize(void);
	void						serialize(void);
};