#ifndef CIDEEntry_AMAT_H
#define CIDEEntry_AMAT_H

#include "bxa.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IDE/Entry/CIDEEntry_Data.h"

class bxa::CIDEEntry_AMAT : public bxa::CIDEEntry_Data
{
public:
	CIDEEntry_AMAT(bxa::CIDEFormat *pIDEFormat) :
		CIDEEntry_Data(pIDEFormat, IDE_SECTION_AMAT)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif