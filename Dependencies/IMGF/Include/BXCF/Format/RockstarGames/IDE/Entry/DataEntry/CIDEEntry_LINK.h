#ifndef CIDEEntry_LINK_H
#define CIDEEntry_LINK_H

#include "bxcf.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IDE/Entry/CIDEEntry_Data.h"

class bxcf::CIDEEntry_LINK : public bxcf::CIDEEntry_Data
{
public:
	CIDEEntry_LINK(bxcf::CIDEFormat *pIDEFormat) :
		CIDEEntry_Data(pIDEFormat, IDE_SECTION_LINK)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif