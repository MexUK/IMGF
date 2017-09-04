#ifndef CRWEntry_2dEffect_SunGlare_H
#define CRWEntry_2dEffect_SunGlare_H

#include "bxcf.h"
#include "Type/Types.h"
#include "Format/RenderWare/Helper/BinaryStream/Entries/C2dEffect.h"
#include <string>

class bxcf::CRWEntry_2dEffect_SunGlare : public bxcf::C2dEffect
{
public:
	CRWEntry_2dEffect_SunGlare(void);

	void							unserialize(void);
	void							serialize(void);
};

#endif