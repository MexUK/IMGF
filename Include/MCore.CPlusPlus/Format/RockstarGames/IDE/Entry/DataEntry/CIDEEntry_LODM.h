#ifndef CIDEEntry_LODM_H
#define CIDEEntry_LODM_H

#include "mcore.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IDE/Entry/CIDEEntry_Data.h"

class mcore::CIDEEntry_LODM : public mcore::CIDEEntry_Data
{
public:
	CIDEEntry_LODM(mcore::CIDEFormat *pIDEFormat) :
		CIDEEntry_Data(pIDEFormat, IDE_SECTION_LODM)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif