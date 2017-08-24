#ifndef CIDEEntry_2DFX_WalkDontWalkAttr_H
#define CIDEEntry_2DFX_WalkDontWalkAttr_H

#include "bxgi.h"
#include "Format/IDE/Entry/DataEntry/CIDEEntry_2DFX.h"

class bxgi::CIDEEntry_2DFX_WalkDontWalkAttr : public bxgi::CIDEEntry_2DFX
{
public:
	CIDEEntry_2DFX_WalkDontWalkAttr(bxgi::CIDEFormat *pIDEFormat) :
		CIDEEntry_2DFX(pIDEFormat, bxgi::_2DFX_WALK_DONT_WALK_ATTR)
	{
	};

	void						unserialize(void);
	void						serialize(void);
};

#endif