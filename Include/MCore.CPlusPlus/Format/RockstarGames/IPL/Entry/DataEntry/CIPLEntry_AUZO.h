#ifndef CIPLEntry_AUZO_H
#define CIPLEntry_AUZO_H

#include "bxa.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IPL/Entry/CIPLEntry_Data.h"
#include "Type/Vector/CVector3D.h"
#include <string>

class bxa::CIPLEntry_AUZO : public bxa::CIPLEntry_Data
{
public:
	CIPLEntry_AUZO(bxa::CIPLFormat *pIPLFormat) :
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

	void						setLowerLeftPosition(bxa::CVector3D& vecLowerLeftPosition) { m_vecLowerLeftPosition = vecLowerLeftPosition; }
	bxa::CVector3D&					getLowerLeftPosition(void) { return m_vecLowerLeftPosition; }

	void						setUpperRightPosition(bxa::CVector3D& vecUpperRightPosition) { m_vecUpperRightPosition = vecUpperRightPosition; }
	bxa::CVector3D&					getUpperRightPosition(void) { return m_vecUpperRightPosition; }

	void						setCenterPosition(bxa::CVector3D& vecCenterPosition) { m_vecCenterPosition = vecCenterPosition; }
	bxa::CVector3D&					getCenterPosition(void) { return m_vecCenterPosition; }

	void						setRadius(float32 fRadius) { m_fRadius = fRadius; }
	float32						getRadius(void) { return m_fRadius; }

private:
	// GTA SA only
	std::string					m_strZoneName;
	uint32						m_uiSoundId;
	uint32						m_uiSwitch;
	bxa::CVector3D					m_vecLowerLeftPosition;
	bxa::CVector3D					m_vecUpperRightPosition;
	bxa::CVector3D					m_vecCenterPosition;
	float32						m_fRadius;
};

#endif