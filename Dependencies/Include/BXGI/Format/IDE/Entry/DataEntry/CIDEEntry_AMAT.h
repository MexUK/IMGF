#ifndef CIDEEntry_AMAT_H
#define CIDEEntry_AMAT_H

#include "bxgi.h"
#include "Type/Types.h"
#include "Format/IDE/Entry/CIDEEntry_Data.h"

class bxgi::CIDEEntry_AMAT : public bxgi::CIDEEntry_Data
{
public:
	CIDEEntry_AMAT(bxgi::CIDEFormat *pIDEFormat) :
		CIDEEntry_Data(pIDEFormat, IDE_SECTION_AMAT)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif