#ifndef CIDEEntry_AMAT_H
#define CIDEEntry_AMAT_H

#include "mcore.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IDE/Entry/CIDEEntry_Data.h"

class mcore::CIDEEntry_AMAT : public mcore::CIDEEntry_Data
{
public:
	CIDEEntry_AMAT(mcore::CIDEFormat *pIDEFormat) :
		CIDEEntry_Data(pIDEFormat, IDE_SECTION_AMAT)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif