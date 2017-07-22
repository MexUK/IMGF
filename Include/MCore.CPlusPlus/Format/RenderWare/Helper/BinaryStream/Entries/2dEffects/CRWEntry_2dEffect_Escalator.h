#ifndef CRWEntry_2dEffect_Escalator_H
#define CRWEntry_2dEffect_Escalator_H

#include "bxa.h"
#include "Type/Types.h"
#include "Format/RenderWare/Helper/BinaryStream/Entries/C2dEffect.h"
#include "Type/Vector/CVector3D.h"
#include <string>

class bxa::CRWEntry_2dEffect_Escalator : public bxa::C2dEffect
{
public:
	CRWEntry_2dEffect_Escalator(void);

	void							unserialize(void);
	void							serialize(void);

	void							setEscalatorBottom(bxa::CVector3D& vecEscalatorBottom) { m_vecEscalatorBottom = vecEscalatorBottom; }
	bxa::CVector3D&						getEscalatorBottom(void) { return m_vecEscalatorBottom; }

	void							setEscalatorTop(bxa::CVector3D& vecEscalatorTop) { m_vecEscalatorTop = vecEscalatorTop; }
	bxa::CVector3D&						getEscalatorTop(void) { return m_vecEscalatorTop; }

	void							setEscalatorEnd(bxa::CVector3D& vecEscalatorEnd) { m_vecEscalatorEnd = vecEscalatorEnd; }
	bxa::CVector3D&						getEscalatorEnd(void) { return m_vecEscalatorEnd; }

	void							setDirection(uint32 uiDirection) { m_uiDirection = uiDirection; }
	uint32							getDirection(void) { return m_uiDirection; }

private:
	bxa::CVector3D						m_vecEscalatorBottom;
	bxa::CVector3D						m_vecEscalatorTop;
	bxa::CVector3D						m_vecEscalatorEnd; // (Z pos, matches top Z if escalator goes up, bottom Z if it goes down)
	uint32							m_uiDirection;
};

#endif