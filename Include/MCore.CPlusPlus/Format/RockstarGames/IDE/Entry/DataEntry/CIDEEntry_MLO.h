#ifndef CIDEEntry_MLO_H
#define CIDEEntry_MLO_H

#include "mcore.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IDE/Entry/CIDEEntry_Data.h"

class mcore::CIDEEntry_MLO : public mcore::CIDEEntry_Data
{
public:
	CIDEEntry_MLO(mcore::CIDEFormat *pIDEFormat) :
		CIDEEntry_Data(pIDEFormat, IDE_SECTION_MLO)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif