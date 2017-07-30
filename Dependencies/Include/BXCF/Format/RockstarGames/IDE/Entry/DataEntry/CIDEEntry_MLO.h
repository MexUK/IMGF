#ifndef CIDEEntry_MLO_H
#define CIDEEntry_MLO_H

#include "bxcf.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IDE/Entry/CIDEEntry_Data.h"

class bxcf::CIDEEntry_MLO : public bxcf::CIDEEntry_Data
{
public:
	CIDEEntry_MLO(bxcf::CIDEFormat *pIDEFormat) :
		CIDEEntry_Data(pIDEFormat, IDE_SECTION_MLO)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif