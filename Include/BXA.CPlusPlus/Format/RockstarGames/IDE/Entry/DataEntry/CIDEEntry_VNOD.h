#ifndef CIDEEntry_VNOD_H
#define CIDEEntry_VNOD_H

#include "BXA.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IDE/Entry/CIDEEntry_Data.h"

class bxa::CIDEEntry_VNOD : public bxa::CIDEEntry_Data
{
public:
	CIDEEntry_VNOD(bxa::CIDEFormat *pIDEFormat) :
		CIDEEntry_Data(pIDEFormat, IDE_SECTION_VNOD)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif