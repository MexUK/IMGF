#ifndef CIDEEntry_VNOD_H
#define CIDEEntry_VNOD_H

#include "bxgi.h"
#include "Type/Types.h"
#include "Format/IDE/Entry/CIDEEntry_Data.h"

class bxgi::CIDEEntry_VNOD : public bxgi::CIDEEntry_Data
{
public:
	CIDEEntry_VNOD(bxgi::CIDEFormat *pIDEFormat) :
		CIDEEntry_Data(pIDEFormat, IDE_SECTION_VNOD)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif