#ifndef CRWSection_2dEffect_H
#define CRWSection_2dEffect_H

#include "BXA.h"
#include "Format/RenderWare/Helper/BinaryStream/CRWSection.h"
#include "Pool/CVectorPool.h"
#include "Format/RenderWare/Helper/BinaryStream/Pools/C2dEffectsPool.h"
#include "Type/Vector/CVector2D.h"
#include "Type/Vector/CVector3D.h"
#include <string>

class bxa::CRWSection_2dEffect : public bxa::CRWSection
{
public:
	CRWSection_2dEffect(void);
	~CRWSection_2dEffect(void);

	void							unserialize(void);
	void							serialize(void);

	bxa::C2dEffectsPool*					get2dEffects(void) { return m_p2dEffectsPool; }

private:
	bxa::C2dEffectsPool*					m_p2dEffectsPool;
};

#endif