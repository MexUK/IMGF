#ifndef CIPLEntry_JUMP_H
#define CIPLEntry_JUMP_H

#include "BXA.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IPL/Entry/CIPLEntry_Data.h"
#include "Type/Vector/CVector3D.h"

class bxa::CIPLEntry_JUMP : public bxa::CIPLEntry_Data
{
public:
	CIPLEntry_JUMP(bxa::CIPLFormat *pIPLFormat) :
		CIPLEntry_Data(pIPLFormat, IPL_SECTION_JUMP),
		m_vecStartLowerPosition{ 0.0f, 0.0f, 0.0f },
		m_vecStartUpperPosition{ 0.0f, 0.0f, 0.0f },
		m_vecTargetLowerPosition{ 0.0f, 0.0f, 0.0f },
		m_vecTargetUpperPosition{ 0.0f, 0.0f, 0.0f },
		m_vecCameraPosition{ 0.0f, 0.0f, 0.0f },
		m_uiReward(0)
	{
	};

	void						unserialize(void);
	void						serialize(void);

	void						setStartLowerPosition(bxa::CVector3D& vecStartLowerPosition) { m_vecStartLowerPosition = vecStartLowerPosition; }
	bxa::CVector3D&					getStartLowerPosition(void) { return m_vecStartLowerPosition; }

	void						setStartUpperPosition(bxa::CVector3D& vecStartUpperPosition) { m_vecStartUpperPosition = vecStartUpperPosition; }
	bxa::CVector3D&					getStartUpperPosition(void) { return m_vecStartUpperPosition; }

	void						setTargetLowerPosition(bxa::CVector3D& vecTargetLowerPosition) { m_vecTargetLowerPosition = vecTargetLowerPosition; }
	bxa::CVector3D&					getTargetLowerPosition(void) { return m_vecTargetLowerPosition; }

	void						setTargetUpperPosition(bxa::CVector3D& vecTargetUpperPosition) { m_vecTargetUpperPosition = vecTargetUpperPosition; }
	bxa::CVector3D&					getTargetUpperPosition(void) { return m_vecTargetUpperPosition; }

	void						setCameraPosition(bxa::CVector3D& vecCameraPosition) { m_vecCameraPosition = vecCameraPosition; }
	bxa::CVector3D&					getCameraPosition(void) { return m_vecCameraPosition; }

	void						setReward(uint32 uiReward) { m_uiReward = uiReward; }
	uint32						getReward(void) { return m_uiReward; }

private:
	// GTA SA only
	bxa::CVector3D					m_vecStartLowerPosition;
	bxa::CVector3D					m_vecStartUpperPosition;
	bxa::CVector3D					m_vecTargetLowerPosition;
	bxa::CVector3D					m_vecTargetUpperPosition;
	bxa::CVector3D					m_vecCameraPosition;
	uint32						m_uiReward;
};

#endif