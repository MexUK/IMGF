#ifndef CRWEntry_2dEffect_Escalator_H
#define CRWEntry_2dEffect_Escalator_H

#include "bxcf.h"
#include "Type/Types.h"
#include "Format/RenderWare/Helper/BinaryStream/Entries/C2dEffect.h"
#include "Type/Vector/CVector3D.h"
#include <string>

class bxcf::CRWEntry_2dEffect_Escalator : public bxcf::C2dEffect
{
public:
	CRWEntry_2dEffect_Escalator(void);

	void							unserialize(void);
	void							serialize(void);

	void							setEscalatorBottom(bxcf::CVector3D& vecEscalatorBottom) { m_vecEscalatorBottom = vecEscalatorBottom; }
	bxcf::CVector3D&						getEscalatorBottom(void) { return m_vecEscalatorBottom; }

	void							setEscalatorTop(bxcf::CVector3D& vecEscalatorTop) { m_vecEscalatorTop = vecEscalatorTop; }
	bxcf::CVector3D&						getEscalatorTop(void) { return m_vecEscalatorTop; }

	void							setEscalatorEnd(bxcf::CVector3D& vecEscalatorEnd) { m_vecEscalatorEnd = vecEscalatorEnd; }
	bxcf::CVector3D&						getEscalatorEnd(void) { return m_vecEscalatorEnd; }

	void							setDirection(uint32 uiDirection) { m_uiDirection = uiDirection; }
	uint32							getDirection(void) { return m_uiDirection; }

private:
	bxcf::CVector3D						m_vecEscalatorBottom;
	bxcf::CVector3D						m_vecEscalatorTop;
	bxcf::CVector3D						m_vecEscalatorEnd; // (Z pos, matches top Z if escalator goes up, bottom Z if it goes down)
	uint32							m_uiDirection;
};

#endif