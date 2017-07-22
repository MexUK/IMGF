#ifndef CIPLEntry_ZONE_H
#define CIPLEntry_ZONE_H

#include "BXA.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IPL/Entry/CIPLEntry_Data.h"
#include "Type/Vector/CVector3D.h"
#include <string>

class bxa::CIPLEntry_ZONE : public bxa::CIPLEntry_Data
{
public:
	CIPLEntry_ZONE(bxa::CIPLFormat *pIPLFormat) :
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

	void						setBottomLeftPosition(bxa::CVector3D& vecBottomLeftPosition) { m_vecBottomLeftPosition = vecBottomLeftPosition; }
	bxa::CVector3D&					getBottomLeftPosition(void) { return m_vecBottomLeftPosition; }

	void						setTopRightPosition(bxa::CVector3D& vecTopRightPosition) { m_vecTopRightPosition = vecTopRightPosition; }
	bxa::CVector3D&					getTopRightPosition(void) { return m_vecTopRightPosition; }

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
	bxa::CVector3D					m_vecBottomLeftPosition;
	bxa::CVector3D					m_vecTopRightPosition;
	uint32						m_uiLevel;
};

#endif