#ifndef CIDEEntry_MLO_H
#define CIDEEntry_MLO_H

#include "bxgi.h"
#include "Type/Types.h"
#include "Format/IDE/Entry/CIDEEntry_Data.h"

class bxgi::CIDEEntry_MLO : public bxgi::CIDEEntry_Data
{
public:
	CIDEEntry_MLO(bxgi::CIDEFormat *pIDEFormat) :
		CIDEEntry_Data(pIDEFormat, IDE_SECTION_MLO)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif