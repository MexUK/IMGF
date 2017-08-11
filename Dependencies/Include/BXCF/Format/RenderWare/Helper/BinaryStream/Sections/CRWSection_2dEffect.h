#ifndef CRWSection_2dEffect_H
#define CRWSection_2dEffect_H

#include "bxcf.h"
#include "Format/RenderWare/Helper/BinaryStream/CRWSection.h"
#include "Pool/CVectorPool.h"
#include "Format/RenderWare/Helper/BinaryStream/Pools/C2dEffectsPool.h"
#include "Type/Vector/Vec2f.h"
#include "Type/Vector/Vec3f.h"
#include <string>

class bxcf::CRWSection_2dEffect : public bxcf::CRWSection
{
public:
	CRWSection_2dEffect(void);
	~CRWSection_2dEffect(void);

	void							unserialize(void);
	void							serialize(void);

	bxcf::C2dEffectsPool*					get2dEffects(void) { return m_p2dEffectsPool; }

private:
	bxcf::C2dEffectsPool*					m_p2dEffectsPool;
};

#endif