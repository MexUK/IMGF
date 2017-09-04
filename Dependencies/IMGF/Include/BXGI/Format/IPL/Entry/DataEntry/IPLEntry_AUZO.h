#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "Format/IPL/Entry/IPLEntry_Data.h"
#include "Type/Vector/Vec3f.h"
#include <string>

class bxgi::IPLEntry_AUZO : public bxgi::IPLEntry_Data
{
public:
	IPLEntry_AUZO(bxgi::IPLFormat *pIPLFormat);

	void						unserialize(void);
	void						serialize(void);

	void						setZoneName(std::string& strZoneName) { m_strZoneName = strZoneName; }
	std::string&				getZoneName(void) { return m_strZoneName; }

	void						setSoundId(uint32 uiSoundID) { m_uiSoundId = uiSoundID; }
	uint32						getSoundId(void) { return m_uiSoundId; }

	void						setLowerLeftPosition(bxcf::Vec3f& vecLowerLeftPosition) { m_vecLowerLeftPosition = vecLowerLeftPosition; }
	bxcf::Vec3f&					getLowerLeftPosition(void) { return m_vecLowerLeftPosition; }

	void						setUpperRightPosition(bxcf::Vec3f& vecUpperRightPosition) { m_vecUpperRightPosition = vecUpperRightPosition; }
	bxcf::Vec3f&					getUpperRightPosition(void) { return m_vecUpperRightPosition; }

	void						setCenterPosition(bxcf::Vec3f& vecCenterPosition) { m_vecCenterPosition = vecCenterPosition; }
	bxcf::Vec3f&					getCenterPosition(void) { return m_vecCenterPosition; }

	void						setRadius(float32 fRadius) { m_fRadius = fRadius; }
	float32						getRadius(void) { return m_fRadius; }

private:
	// GTA SA only
	std::string					m_strZoneName;
	uint32						m_uiSoundId;
	uint32						m_uiSwitch;
	bxcf::Vec3f					m_vecLowerLeftPosition;
	bxcf::Vec3f					m_vecUpperRightPosition;
	bxcf::Vec3f					m_vecCenterPosition;
	float32						m_fRadius;
};