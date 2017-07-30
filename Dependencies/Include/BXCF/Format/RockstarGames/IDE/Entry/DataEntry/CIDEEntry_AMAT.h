#ifndef CIDEEntry_AMAT_H
#define CIDEEntry_AMAT_H

#include "bxcf.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IDE/Entry/CIDEEntry_Data.h"

class bxcf::CIDEEntry_AMAT : public bxcf::CIDEEntry_Data
{
public:
	CIDEEntry_AMAT(bxcf::CIDEFormat *pIDEFormat) :
		CIDEEntry_Data(pIDEFormat, IDE_SECTION_AMAT)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif