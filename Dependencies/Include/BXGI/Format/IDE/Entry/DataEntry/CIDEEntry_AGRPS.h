#ifndef CIDEEntry_AGRPS_H
#define CIDEEntry_AGRPS_H

#include "bxgi.h"
#include "Type/Types.h"
#include "Format/IDE/Entry/CIDEEntry_Data.h"

class bxgi::CIDEEntry_AGRPS: public bxgi::CIDEEntry_Data
{
public:
	CIDEEntry_AGRPS(bxgi::CIDEFormat *pIDEFormat) :
		CIDEEntry_Data(pIDEFormat, IDE_SECTION_AGRPS)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif