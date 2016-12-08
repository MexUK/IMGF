#ifndef CIDEEntry_TREE_H
#define CIDEEntry_TREE_H

#include "mcore.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IDE/Entry/CIDEEntry_Data.h"

class mcore::CIDEEntry_TREE : public mcore::CIDEEntry_Data
{
public:
	CIDEEntry_TREE(mcore::CIDEFormat *pIDEFormat) :
		CIDEEntry_Data(pIDEFormat, IDE_SECTION_TREE)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif