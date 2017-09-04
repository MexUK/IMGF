#ifndef CIDEEntry_TANM_H
#define CIDEEntry_TANM_H

#include "bxcf.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IDE/Entry/CIDEEntry_Data.h"

class bxcf::CIDEEntry_TANM : public bxcf::CIDEEntry_Data
{
public:
	CIDEEntry_TANM(bxcf::CIDEFormat *pIDEFormat) :
		CIDEEntry_Data(pIDEFormat, IDE_SECTION_TANM)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif