#ifndef CIDEEntry_AGRPS_H
#define CIDEEntry_AGRPS_H

#include "mcore.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IDE/Entry/CIDEEntry_Data.h"

class mcore::CIDEEntry_AGRPS: public mcore::CIDEEntry_Data
{
public:
	CIDEEntry_AGRPS(mcore::CIDEFormat *pIDEFormat) :
		CIDEEntry_Data(pIDEFormat, IDE_SECTION_AGRPS)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif