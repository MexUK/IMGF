#ifndef CIDEEntry_LINK_H
#define CIDEEntry_LINK_H

#include "bxgi.h"
#include "Type/Types.h"
#include "Format/IDE/Entry/CIDEEntry_Data.h"

class bxgi::CIDEEntry_LINK : public bxgi::CIDEEntry_Data
{
public:
	CIDEEntry_LINK(bxgi::CIDEFormat *pIDEFormat) :
		CIDEEntry_Data(pIDEFormat, IDE_SECTION_LINK)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif