#ifndef CIDEEntry_LODM_H
#define CIDEEntry_LODM_H

#include "bxcf.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IDE/Entry/CIDEEntry_Data.h"

class bxcf::CIDEEntry_LODM : public bxcf::CIDEEntry_Data
{
public:
	CIDEEntry_LODM(bxcf::CIDEFormat *pIDEFormat) :
		CIDEEntry_Data(pIDEFormat, IDE_SECTION_LODM)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif