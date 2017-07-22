#ifndef CIDEEntry_TANM_H
#define CIDEEntry_TANM_H

#include "bxa.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IDE/Entry/CIDEEntry_Data.h"

class bxa::CIDEEntry_TANM : public bxa::CIDEEntry_Data
{
public:
	CIDEEntry_TANM(bxa::CIDEFormat *pIDEFormat) :
		CIDEEntry_Data(pIDEFormat, IDE_SECTION_TANM)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif