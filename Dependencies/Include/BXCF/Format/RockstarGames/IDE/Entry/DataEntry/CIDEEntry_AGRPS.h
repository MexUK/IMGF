#ifndef CIDEEntry_AGRPS_H
#define CIDEEntry_AGRPS_H

#include "bxcf.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IDE/Entry/CIDEEntry_Data.h"

class bxcf::CIDEEntry_AGRPS: public bxcf::CIDEEntry_Data
{
public:
	CIDEEntry_AGRPS(bxcf::CIDEFormat *pIDEFormat) :
		CIDEEntry_Data(pIDEFormat, IDE_SECTION_AGRPS)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif