#ifndef CIDEEntry_TREE_H
#define CIDEEntry_TREE_H

#include "bxa.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IDE/Entry/CIDEEntry_Data.h"

class bxa::CIDEEntry_TREE : public bxa::CIDEEntry_Data
{
public:
	CIDEEntry_TREE(bxa::CIDEFormat *pIDEFormat) :
		CIDEEntry_Data(pIDEFormat, IDE_SECTION_TREE)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif