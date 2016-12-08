#ifndef CIDEEntry_TANM_H
#define CIDEEntry_TANM_H

#include "mcore.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IDE/Entry/CIDEEntry_Data.h"

class mcore::CIDEEntry_TANM : public mcore::CIDEEntry_Data
{
public:
	CIDEEntry_TANM(mcore::CIDEFormat *pIDEFormat) :
		CIDEEntry_Data(pIDEFormat, IDE_SECTION_TANM)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif