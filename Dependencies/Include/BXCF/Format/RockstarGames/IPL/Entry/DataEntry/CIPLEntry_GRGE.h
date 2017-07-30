#ifndef CIPLEntry_GRGE_H
#define CIPLEntry_GRGE_H

#include "bxcf.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IPL/Entry/CIPLEntry_Data.h"
#include "Type/Vector/CVector2D.h"
#include "Type/Vector/CVector3D.h"
#include <string>

class bxcf::CIPLEntry_GRGE : public bxcf::CIPLEntry_Data
{
public:
	CIPLEntry_GRGE(bxcf::CIPLFormat *pIPLFormat) :
		CIPLEntry_Data(pIPLFormat, IPL_SECTION_GRGE),
		m_vecPosition{ 0.0f, 0.0f, 0.0f },
		m_vecLine{ 0.0f, 0.0f },
		m_vecCubePosition{ 0.0f, 0.0f, 0.0f },
		m_uiGarageFlags(0),
		m_uiGarageType(0)
	{
	};

	void						unserialize(void);
	void						serialize(void);

	void						setPosition(bxcf::CVector3D& vecPosition) { m_vecPosition = vecPosition; }
	bxcf::CVector3D&					getPosition(void) { return m_vecPosition; }

	void						setLine(bxcf::CVector2D& vecLine) { m_vecLine = vecLine; }
	bxcf::CVector2D&					getLine(void) { return m_vecLine; }

	void						setCubePosition(bxcf::CVector3D& vecCubePosition) { m_vecCubePosition = vecCubePosition; }
	bxcf::CVector3D&					getCubePosition(void) { return m_vecCubePosition; }

	void						setGarageFlags(uint32 uiGarageFlags) { m_uiGarageFlags = uiGarageFlags; }
	uint32						getGarageFlags(void) { return m_uiGarageFlags; }

	void						setGarageType(uint32 uiGarageType) { m_uiGarageType = uiGarageType; }
	uint32						getGarageType(void) { return m_uiGarageType; }

	void						setGarageName(std::string& strGarageName) { m_strGarageName = strGarageName; }
	std::string&				getGarageName(void) { return m_strGarageName; }

private:
	// GTA SA only
	bxcf::CVector3D					m_vecPosition;
	bxcf::CVector2D					m_vecLine;
	bxcf::CVector3D					m_vecCubePosition;
	uint32						m_uiGarageFlags;
	uint32						m_uiGarageType;
	std::string					m_strGarageName;
};

#endif