#ifndef CIDEEntry_LODM_H
#define CIDEEntry_LODM_H

#include "bxgi.h"
#include "Type/Types.h"
#include "Format/IDE/Entry/CIDEEntry_Data.h"

class bxgi::CIDEEntry_LODM : public bxgi::CIDEEntry_Data
{
public:
	CIDEEntry_LODM(bxgi::CIDEFormat *pIDEFormat) :
		CIDEEntry_Data(pIDEFormat, IDE_SECTION_LODM)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif