#ifndef CIDEEntry_TREE_H
#define CIDEEntry_TREE_H

#include "bxcf.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IDE/Entry/CIDEEntry_Data.h"

class bxcf::CIDEEntry_TREE : public bxcf::CIDEEntry_Data
{
public:
	CIDEEntry_TREE(bxcf::CIDEFormat *pIDEFormat) :
		CIDEEntry_Data(pIDEFormat, IDE_SECTION_TREE)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif