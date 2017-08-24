#ifndef CIDEEntry_TREE_H
#define CIDEEntry_TREE_H

#include "bxgi.h"
#include "Type/Types.h"
#include "Format/IDE/Entry/CIDEEntry_Data.h"

class bxgi::CIDEEntry_TREE : public bxgi::CIDEEntry_Data
{
public:
	CIDEEntry_TREE(bxgi::CIDEFormat *pIDEFormat) :
		CIDEEntry_Data(pIDEFormat, IDE_SECTION_TREE)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif