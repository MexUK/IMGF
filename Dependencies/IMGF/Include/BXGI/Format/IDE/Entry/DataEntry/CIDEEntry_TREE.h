#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "Format/IDE/Entry/CIDEEntry_Data.h"

class bxgi::CIDEEntry_TREE : public bxgi::CIDEEntry_Data
{
public:
	CIDEEntry_TREE(bxgi::CIDEFormat *pIDEFormat);

	void						unserialize(void);
	void						serialize(void);
};