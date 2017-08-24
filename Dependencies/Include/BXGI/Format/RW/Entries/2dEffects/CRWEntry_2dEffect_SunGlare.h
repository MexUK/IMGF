#ifndef CRWEntry_2dEffect_SunGlare_H
#define CRWEntry_2dEffect_SunGlare_H

#include "bxgi.h"
#include "Type/Types.h"
#include "Format/RW/Entries/C2dEffect.h"

class bxgi::CRWEntry_2dEffect_SunGlare : public bxgi::C2dEffect
{
public:
	CRWEntry_2dEffect_SunGlare(void);

	void							unserialize(void);
	void							serialize(void);
};

#endif