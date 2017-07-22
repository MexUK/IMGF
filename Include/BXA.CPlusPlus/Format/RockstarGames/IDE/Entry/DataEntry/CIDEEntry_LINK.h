#ifndef CIDEEntry_LINK_H
#define CIDEEntry_LINK_H

#include "BXA.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IDE/Entry/CIDEEntry_Data.h"

class bxa::CIDEEntry_LINK : public bxa::CIDEEntry_Data
{
public:
	CIDEEntry_LINK(bxa::CIDEFormat *pIDEFormat) :
		CIDEEntry_Data(pIDEFormat, IDE_SECTION_LINK)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif