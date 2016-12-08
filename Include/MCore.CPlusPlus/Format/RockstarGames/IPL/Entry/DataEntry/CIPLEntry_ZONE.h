#ifndef CIPLEntry_ZONE_H
#define CIPLEntry_ZONE_H

#include "mcore.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IPL/Entry/CIPLEntry_Data.h"
#include "Type/Vector/CVector3D.h"
#include <string>

class mcore::CIPLEntry_ZONE : public mcore::CIPLEntry_Data
{
public:
	CIPLEntry_ZONE(mcore::CIPLFormat *pIPLFormat) :
		CIPLEntry_Data(pIPLFormat, IPL_SECTION_ZONE),
		m_uiZoneType(0),
		m_vecBottomLeftPosition{ 0.0f, 0.0f, 0.0f },
		m_vecTopRightPosition{ 0.0f, 0.0f, 0.0f },
		m_uiLevel(0)
	{
	};

	void						unserialize(void);
	void						serialize(void);

	void						setZoneName(std::string& strZoneName) { m_strZoneName = strZoneName; }
	std::string&				getZoneName(void) { return m_strZoneName; }

	void						setZoneType(uint32 uiZoneType) { m_uiZoneType = uiZoneType; }
	uint32						getZoneType(void) { return m_uiZoneType; }

	void						setBottomLeftPosition(mcore::CVector3D& vecBottomLeftPosition) { m_vecBottomLeftPosition = vecBottomLeftPosition; }
	mcore::CVector3D&					getBottomLeftPosition(void) { return m_vecBottomLeftPosition; }

	void						setTopRightPosition(mcore::CVector3D& vecTopRightPosition) { m_vecTopRightPosition = vecTopRightPosition; }
	mcore::CVector3D&					getTopRightPosition(void) { return m_vecTopRightPosition; }

	void						setLevel(uint32 uiLevel) { m_uiLevel = uiLevel; }
	uint32						getLevel(void) { return m_uiLevel; }

	void						setZoneText(std::string& strZoneText) { m_strZoneText = strZoneText; }
	std::string&				getZoneText(void) { return m_strZoneText; }

private:
	// GTA SA & GTA IV
	std::string					m_strZoneText;

	// GTA III era only
	std::string					m_strZoneName;
	uint32						m_uiZoneType;
	mcore::CVector3D					m_vecBottomLeftPosition;
	mcore::CVector3D					m_vecTopRightPosition;
	uint32						m_uiLevel;
};

#endif