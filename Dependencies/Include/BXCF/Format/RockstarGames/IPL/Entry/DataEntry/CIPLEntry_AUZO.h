#ifndef CIPLEntry_AUZO_H
#define CIPLEntry_AUZO_H

#include "bxcf.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IPL/Entry/CIPLEntry_Data.h"
#include "Type/Vector/CVector3D.h"
#include <string>

class bxcf::CIPLEntry_AUZO : public bxcf::CIPLEntry_Data
{
public:
	CIPLEntry_AUZO(bxcf::CIPLFormat *pIPLFormat) :
		CIPLEntry_Data(pIPLFormat, IPL_SECTION_AUZO),
		m_uiSoundId(0),
		m_uiSwitch(0),
		m_vecLowerLeftPosition{ 0.0f, 0.0f, 0.0f },
		m_vecUpperRightPosition{ 0.0f, 0.0f, 0.0f },
		m_vecCenterPosition{ 0.0f, 0.0f, 0.0f },
		m_fRadius(0.0f)
	{
	};

	void						unserialize(void);
	void						serialize(void);

	void						setZoneName(std::string& strZoneName) { m_strZoneName = strZoneName; }
	std::string&				getZoneName(void) { return m_strZoneName; }

	void						setSoundId(uint32 uiSoundID) { m_uiSoundId = uiSoundID; }
	uint32						getSoundId(void) { return m_uiSoundId; }

	void						setLowerLeftPosition(bxcf::CVector3D& vecLowerLeftPosition) { m_vecLowerLeftPosition = vecLowerLeftPosition; }
	bxcf::CVector3D&					getLowerLeftPosition(void) { return m_vecLowerLeftPosition; }

	void						setUpperRightPosition(bxcf::CVector3D& vecUpperRightPosition) { m_vecUpperRightPosition = vecUpperRightPosition; }
	bxcf::CVector3D&					getUpperRightPosition(void) { return m_vecUpperRightPosition; }

	void						setCenterPosition(bxcf::CVector3D& vecCenterPosition) { m_vecCenterPosition = vecCenterPosition; }
	bxcf::CVector3D&					getCenterPosition(void) { return m_vecCenterPosition; }

	void						setRadius(float32 fRadius) { m_fRadius = fRadius; }
	float32						getRadius(void) { return m_fRadius; }

private:
	// GTA SA only
	std::string					m_strZoneName;
	uint32						m_uiSoundId;
	uint32						m_uiSwitch;
	bxcf::CVector3D					m_vecLowerLeftPosition;
	bxcf::CVector3D					m_vecUpperRightPosition;
	bxcf::CVector3D					m_vecCenterPosition;
	float32						m_fRadius;
};

#endif