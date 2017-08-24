#ifndef CIPLEntry_GRGE_H
#define CIPLEntry_GRGE_H

#include "bxgi.h"
#include "Type/Types.h"
#include "Format/IPL/Entry/CIPLEntry_Data.h"
#include "Type/Vector/Vec2f.h"
#include "Type/Vector/Vec3f.h"
#include <string>

class bxgi::CIPLEntry_GRGE : public bxgi::CIPLEntry_Data
{
public:
	CIPLEntry_GRGE(bxgi::CIPLFormat *pIPLFormat) :
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

	void						setPosition(bxcf::Vec3f& vecPosition) { m_vecPosition = vecPosition; }
	bxcf::Vec3f&					getPosition(void) { return m_vecPosition; }

	void						setLine(bxcf::Vec2f& vecLine) { m_vecLine = vecLine; }
	bxcf::Vec2f&					getLine(void) { return m_vecLine; }

	void						setCubePosition(bxcf::Vec3f& vecCubePosition) { m_vecCubePosition = vecCubePosition; }
	bxcf::Vec3f&					getCubePosition(void) { return m_vecCubePosition; }

	void						setGarageFlags(uint32 uiGarageFlags) { m_uiGarageFlags = uiGarageFlags; }
	uint32						getGarageFlags(void) { return m_uiGarageFlags; }

	void						setGarageType(uint32 uiGarageType) { m_uiGarageType = uiGarageType; }
	uint32						getGarageType(void) { return m_uiGarageType; }

	void						setGarageName(std::string& strGarageName) { m_strGarageName = strGarageName; }
	std::string&				getGarageName(void) { return m_strGarageName; }

private:
	// GTA SA only
	bxcf::Vec3f					m_vecPosition;
	bxcf::Vec2f					m_vecLine;
	bxcf::Vec3f					m_vecCubePosition;
	uint32						m_uiGarageFlags;
	uint32						m_uiGarageType;
	std::string					m_strGarageName;
};

#endif