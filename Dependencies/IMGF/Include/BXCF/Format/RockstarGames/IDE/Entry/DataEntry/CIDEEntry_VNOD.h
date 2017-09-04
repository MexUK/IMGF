#ifndef CIDEEntry_VNOD_H
#define CIDEEntry_VNOD_H

#include "bxcf.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IDE/Entry/CIDEEntry_Data.h"

class bxcf::CIDEEntry_VNOD : public bxcf::CIDEEntry_Data
{
public:
	CIDEEntry_VNOD(bxcf::CIDEFormat *pIDEFormat) :
		CIDEEntry_Data(pIDEFormat, IDE_SECTION_VNOD)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif