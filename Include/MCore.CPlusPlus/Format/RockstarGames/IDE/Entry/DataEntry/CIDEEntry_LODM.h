#ifndef CIDEEntry_LODM_H
#define CIDEEntry_LODM_H

#include "bxa.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IDE/Entry/CIDEEntry_Data.h"

class bxa::CIDEEntry_LODM : public bxa::CIDEEntry_Data
{
public:
	CIDEEntry_LODM(bxa::CIDEFormat *pIDEFormat) :
		CIDEEntry_Data(pIDEFormat, IDE_SECTION_LODM)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif