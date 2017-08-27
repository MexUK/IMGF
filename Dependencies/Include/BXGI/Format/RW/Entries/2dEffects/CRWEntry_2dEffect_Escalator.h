#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "Format/RW/Entries/C2dEffect.h"
#include "Type/Vector/Vec3f.h"

class bxgi::CRWEntry_2dEffect_Escalator : public bxgi::C2dEffect
{
public:
	CRWEntry_2dEffect_Escalator(void);

	void							unserialize(void);
	void							serialize(void);

	void							setEscalatorBottom(bxcf::Vec3f& vecEscalatorBottom) { m_vecEscalatorBottom = vecEscalatorBottom; }
	bxcf::Vec3f&					getEscalatorBottom(void) { return m_vecEscalatorBottom; }

	void							setEscalatorTop(bxcf::Vec3f& vecEscalatorTop) { m_vecEscalatorTop = vecEscalatorTop; }
	bxcf::Vec3f&					getEscalatorTop(void) { return m_vecEscalatorTop; }

	void							setEscalatorEnd(bxcf::Vec3f& vecEscalatorEnd) { m_vecEscalatorEnd = vecEscalatorEnd; }
	bxcf::Vec3f&					getEscalatorEnd(void) { return m_vecEscalatorEnd; }

	void							setDirection(uint32 uiDirection) { m_uiDirection = uiDirection; }
	uint32							getDirection(void) { return m_uiDirection; }

private:
	bxcf::Vec3f						m_vecEscalatorBottom;
	bxcf::Vec3f						m_vecEscalatorTop;
	bxcf::Vec3f						m_vecEscalatorEnd; // (Z pos, matches top Z if escalator goes up, bottom Z if it goes down)
	uint32							m_uiDirection;
};