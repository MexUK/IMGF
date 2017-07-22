#ifndef CIDEEntry_AGRPS_H
#define CIDEEntry_AGRPS_H

#include "BXA.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IDE/Entry/CIDEEntry_Data.h"

class bxa::CIDEEntry_AGRPS: public bxa::CIDEEntry_Data
{
public:
	CIDEEntry_AGRPS(bxa::CIDEFormat *pIDEFormat) :
		CIDEEntry_Data(pIDEFormat, IDE_SECTION_AGRPS)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif