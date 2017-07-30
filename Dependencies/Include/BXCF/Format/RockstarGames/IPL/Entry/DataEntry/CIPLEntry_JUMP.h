#ifndef CIPLEntry_JUMP_H
#define CIPLEntry_JUMP_H

#include "bxcf.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IPL/Entry/CIPLEntry_Data.h"
#include "Type/Vector/CVector3D.h"

class bxcf::CIPLEntry_JUMP : public bxcf::CIPLEntry_Data
{
public:
	CIPLEntry_JUMP(bxcf::CIPLFormat *pIPLFormat) :
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

	void						setStartLowerPosition(bxcf::CVector3D& vecStartLowerPosition) { m_vecStartLowerPosition = vecStartLowerPosition; }
	bxcf::CVector3D&					getStartLowerPosition(void) { return m_vecStartLowerPosition; }

	void						setStartUpperPosition(bxcf::CVector3D& vecStartUpperPosition) { m_vecStartUpperPosition = vecStartUpperPosition; }
	bxcf::CVector3D&					getStartUpperPosition(void) { return m_vecStartUpperPosition; }

	void						setTargetLowerPosition(bxcf::CVector3D& vecTargetLowerPosition) { m_vecTargetLowerPosition = vecTargetLowerPosition; }
	bxcf::CVector3D&					getTargetLowerPosition(void) { return m_vecTargetLowerPosition; }

	void						setTargetUpperPosition(bxcf::CVector3D& vecTargetUpperPosition) { m_vecTargetUpperPosition = vecTargetUpperPosition; }
	bxcf::CVector3D&					getTargetUpperPosition(void) { return m_vecTargetUpperPosition; }

	void						setCameraPosition(bxcf::CVector3D& vecCameraPosition) { m_vecCameraPosition = vecCameraPosition; }
	bxcf::CVector3D&					getCameraPosition(void) { return m_vecCameraPosition; }

	void						setReward(uint32 uiReward) { m_uiReward = uiReward; }
	uint32						getReward(void) { return m_uiReward; }

private:
	// GTA SA only
	bxcf::CVector3D					m_vecStartLowerPosition;
	bxcf::CVector3D					m_vecStartUpperPosition;
	bxcf::CVector3D					m_vecTargetLowerPosition;
	bxcf::CVector3D					m_vecTargetUpperPosition;
	bxcf::CVector3D					m_vecCameraPosition;
	uint32						m_uiReward;
};

#endif