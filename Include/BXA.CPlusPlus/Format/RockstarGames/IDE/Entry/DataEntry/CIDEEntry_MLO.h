#ifndef CIDEEntry_MLO_H
#define CIDEEntry_MLO_H

#include "BXA.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IDE/Entry/CIDEEntry_Data.h"

class bxa::CIDEEntry_MLO : public bxa::CIDEEntry_Data
{
public:
	CIDEEntry_MLO(bxa::CIDEFormat *pIDEFormat) :
		CIDEEntry_Data(pIDEFormat, IDE_SECTION_MLO)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif