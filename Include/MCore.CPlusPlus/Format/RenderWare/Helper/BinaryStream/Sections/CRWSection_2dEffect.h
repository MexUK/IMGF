#ifndef CRWSection_2dEffect_H
#define CRWSection_2dEffect_H

#include "mcore.h"
#include "Format/RenderWare/Helper/BinaryStream/CRWSection.h"
#include "Pool/CVectorPool.h"
#include "Format/RenderWare/Helper/BinaryStream/Pools/C2dEffectsPool.h"
#include "Type/Vector/CVector2D.h"
#include "Type/Vector/CVector3D.h"
#include <string>

class mcore::CRWSection_2dEffect : public mcore::CRWSection
{
public:
	CRWSection_2dEffect(void);
	~CRWSection_2dEffect(void);

	void							unserialize(void);
	void							serialize(void);

	mcore::C2dEffectsPool*					get2dEffects(void) { return m_p2dEffectsPool; }

private:
	mcore::C2dEffectsPool*					m_p2dEffectsPool;
};

#endif