#ifndef CIDEEntry_VNOD_H
#define CIDEEntry_VNOD_H

#include "mcore.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IDE/Entry/CIDEEntry_Data.h"

class mcore::CIDEEntry_VNOD : public mcore::CIDEEntry_Data
{
public:
	CIDEEntry_VNOD(mcore::CIDEFormat *pIDEFormat) :
		CIDEEntry_Data(pIDEFormat, IDE_SECTION_VNOD)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif