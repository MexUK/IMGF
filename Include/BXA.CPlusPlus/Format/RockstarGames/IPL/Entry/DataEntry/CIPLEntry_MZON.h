#ifndef CIPLEntry_MZON_H
#define CIPLEntry_MZON_H

#include "BXA.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IPL/Entry/CIPLEntry_Data.h"
#include "Type/Vector/CVector3D.h"

class bxa::CIPLEntry_MZON : public bxa::CIPLEntry_Data
{
public:
	CIPLEntry_MZON(bxa::CIPLFormat *pIPLFormat) :
		CIPLEntry_Data(pIPLFormat, IPL_SECTION_MZON)
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
	// GTA IV only
	std::string					m_strZoneName;
	uint32						m_uiZoneType;
	bxa::CVector3D					m_vecBottomLeftPosition;
	bxa::CVector3D					m_vecTopRightPosition;
	uint32						m_uiLevel;
	std::string					m_strZoneText;
};

#endif