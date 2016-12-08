#ifndef CIPLEntry_JUMP_H
#define CIPLEntry_JUMP_H

#include "mcore.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IPL/Entry/CIPLEntry_Data.h"
#include "Type/Vector/CVector3D.h"

class mcore::CIPLEntry_JUMP : public mcore::CIPLEntry_Data
{
public:
	CIPLEntry_JUMP(mcore::CIPLFormat *pIPLFormat) :
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

	void						setStartLowerPosition(mcore::CVector3D& vecStartLowerPosition) { m_vecStartLowerPosition = vecStartLowerPosition; }
	mcore::CVector3D&					getStartLowerPosition(void) { return m_vecStartLowerPosition; }

	void						setStartUpperPosition(mcore::CVector3D& vecStartUpperPosition) { m_vecStartUpperPosition = vecStartUpperPosition; }
	mcore::CVector3D&					getStartUpperPosition(void) { return m_vecStartUpperPosition; }

	void						setTargetLowerPosition(mcore::CVector3D& vecTargetLowerPosition) { m_vecTargetLowerPosition = vecTargetLowerPosition; }
	mcore::CVector3D&					getTargetLowerPosition(void) { return m_vecTargetLowerPosition; }

	void						setTargetUpperPosition(mcore::CVector3D& vecTargetUpperPosition) { m_vecTargetUpperPosition = vecTargetUpperPosition; }
	mcore::CVector3D&					getTargetUpperPosition(void) { return m_vecTargetUpperPosition; }

	void						setCameraPosition(mcore::CVector3D& vecCameraPosition) { m_vecCameraPosition = vecCameraPosition; }
	mcore::CVector3D&					getCameraPosition(void) { return m_vecCameraPosition; }

	void						setReward(uint32 uiReward) { m_uiReward = uiReward; }
	uint32						getReward(void) { return m_uiReward; }

private:
	// GTA SA only
	mcore::CVector3D					m_vecStartLowerPosition;
	mcore::CVector3D					m_vecStartUpperPosition;
	mcore::CVector3D					m_vecTargetLowerPosition;
	mcore::CVector3D					m_vecTargetUpperPosition;
	mcore::CVector3D					m_vecCameraPosition;
	uint32						m_uiReward;
};

#endif