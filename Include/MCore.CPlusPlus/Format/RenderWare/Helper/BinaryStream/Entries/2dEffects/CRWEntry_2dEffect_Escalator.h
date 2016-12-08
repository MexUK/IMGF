#ifndef CRWEntry_2dEffect_Escalator_H
#define CRWEntry_2dEffect_Escalator_H

#include "mcore.h"
#include "Type/Types.h"
#include "Format/RenderWare/Helper/BinaryStream/Entries/C2dEffect.h"
#include "Type/Vector/CVector3D.h"
#include <string>

class mcore::CRWEntry_2dEffect_Escalator : public mcore::C2dEffect
{
public:
	CRWEntry_2dEffect_Escalator(void);

	void							unserialize(void);
	void							serialize(void);

	void							setEscalatorBottom(mcore::CVector3D& vecEscalatorBottom) { m_vecEscalatorBottom = vecEscalatorBottom; }
	mcore::CVector3D&						getEscalatorBottom(void) { return m_vecEscalatorBottom; }

	void							setEscalatorTop(mcore::CVector3D& vecEscalatorTop) { m_vecEscalatorTop = vecEscalatorTop; }
	mcore::CVector3D&						getEscalatorTop(void) { return m_vecEscalatorTop; }

	void							setEscalatorEnd(mcore::CVector3D& vecEscalatorEnd) { m_vecEscalatorEnd = vecEscalatorEnd; }
	mcore::CVector3D&						getEscalatorEnd(void) { return m_vecEscalatorEnd; }

	void							setDirection(uint32 uiDirection) { m_uiDirection = uiDirection; }
	uint32							getDirection(void) { return m_uiDirection; }

private:
	mcore::CVector3D						m_vecEscalatorBottom;
	mcore::CVector3D						m_vecEscalatorTop;
	mcore::CVector3D						m_vecEscalatorEnd; // (Z pos, matches top Z if escalator goes up, bottom Z if it goes down)
	uint32							m_uiDirection;
};

#endif