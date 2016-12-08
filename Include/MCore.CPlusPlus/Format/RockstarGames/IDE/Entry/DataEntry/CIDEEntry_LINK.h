#ifndef CIDEEntry_LINK_H
#define CIDEEntry_LINK_H

#include "mcore.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IDE/Entry/CIDEEntry_Data.h"

class mcore::CIDEEntry_LINK : public mcore::CIDEEntry_Data
{
public:
	CIDEEntry_LINK(mcore::CIDEFormat *pIDEFormat) :
		CIDEEntry_Data(pIDEFormat, IDE_SECTION_LINK)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif