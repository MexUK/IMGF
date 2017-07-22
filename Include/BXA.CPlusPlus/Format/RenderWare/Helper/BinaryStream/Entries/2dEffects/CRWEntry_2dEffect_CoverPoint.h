#ifndef CRWEntry_2dEffect_CoverPoint_H
#define CRWEntry_2dEffect_CoverPoint_H

#include "BXA.h"
#include "Type/Types.h"
#include "Format/RenderWare/Helper/BinaryStream/Entries/C2dEffect.h"
#include "Type/Vector/CVector2D.h"
#include <string>

class bxa::CRWEntry_2dEffect_CoverPoint : public bxa::C2dEffect
{
public:
	CRWEntry_2dEffect_CoverPoint(void);

	void							unserialize(void);
	void							serialize(void);

	void							setDirection(bxa::CVector2D& vecDirection) { m_vecDirection = vecDirection; }
	bxa::CVector2D&						getDirection(void) { return m_vecDirection; }

	void							setCoverType(uint32 uiCoverType) { m_uiCoverType = uiCoverType; }
	uint32							getCoverType(void) { return m_uiCoverType; }

private:
	bxa::CVector2D						m_vecDirection;
	uint32							m_uiCoverType;
};

#endif