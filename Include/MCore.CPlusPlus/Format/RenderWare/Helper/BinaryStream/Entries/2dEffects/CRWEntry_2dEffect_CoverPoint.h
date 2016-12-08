#ifndef CRWEntry_2dEffect_CoverPoint_H
#define CRWEntry_2dEffect_CoverPoint_H

#include "mcore.h"
#include "Type/Types.h"
#include "Format/RenderWare/Helper/BinaryStream/Entries/C2dEffect.h"
#include "Type/Vector/CVector2D.h"
#include <string>

class mcore::CRWEntry_2dEffect_CoverPoint : public mcore::C2dEffect
{
public:
	CRWEntry_2dEffect_CoverPoint(void);

	void							unserialize(void);
	void							serialize(void);

	void							setDirection(mcore::CVector2D& vecDirection) { m_vecDirection = vecDirection; }
	mcore::CVector2D&						getDirection(void) { return m_vecDirection; }

	void							setCoverType(uint32 uiCoverType) { m_uiCoverType = uiCoverType; }
	uint32							getCoverType(void) { return m_uiCoverType; }

private:
	mcore::CVector2D						m_vecDirection;
	uint32							m_uiCoverType;
};

#endif