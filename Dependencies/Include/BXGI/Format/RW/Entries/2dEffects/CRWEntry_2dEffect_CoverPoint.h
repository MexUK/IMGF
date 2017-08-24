#ifndef CRWEntry_2dEffect_CoverPoint_H
#define CRWEntry_2dEffect_CoverPoint_H

#include "bxgi.h"
#include "Type/Types.h"
#include "Format/RW/Entries/C2dEffect.h"
#include "Type/Vector/Vec2f.h"

class bxgi::CRWEntry_2dEffect_CoverPoint : public bxgi::C2dEffect
{
public:
	CRWEntry_2dEffect_CoverPoint(void);

	void							unserialize(void);
	void							serialize(void);

	void							setDirection(bxcf::Vec2f& vecDirection) { m_vecDirection = vecDirection; }
	bxcf::Vec2f&					getDirection(void) { return m_vecDirection; }

	void							setCoverType(uint32 uiCoverType) { m_uiCoverType = uiCoverType; }
	uint32							getCoverType(void) { return m_uiCoverType; }

private:
	bxcf::Vec2f						m_vecDirection;
	uint32							m_uiCoverType;
};

#endif