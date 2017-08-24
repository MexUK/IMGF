#ifndef CIPLEntry_ENEX_H
#define CIPLEntry_ENEX_H

#include "bxgi.h"
#include "Type/Types.h"
#include "Type/Vector/Vec2f.h"
#include "Type/Vector/Vec3f.h"
#include "Format/IPL/Entry/CIPLEntry_Data.h"
#include <string>

class bxgi::CIPLEntry_ENEX : public bxgi::CIPLEntry_Data
{
public:
	CIPLEntry_ENEX(bxgi::CIPLFormat *pIPLFormat) :
		CIPLEntry_Data(pIPLFormat, IPL_SECTION_ENEX),
		m_vecEntrancePosition{ 0.0f, 0.0f, 0.0f },
		m_fRotation(0.0f),
		m_vecSize{ 0.0f, 0.0f },
		m_uiConstant8(0),
		m_vecExitPosition{ 0.0f, 0.0f, 0.0f },
		m_fExitRotation(0.0f),
		m_uiTargetInterior(0),
		m_uiMarkerType(0),
		m_uiSkyColourChanger(0),
		m_uiUnknown1(0),
		m_uiTimeOn(0),
		m_uiTimeOff(0)
	{
	};

	void						unserialize(void);
	void						serialize(void);

	void						setEntrancePosition(bxcf::Vec3f& vecEntrancePosition) { m_vecEntrancePosition = vecEntrancePosition; }
	bxcf::Vec3f&					getEntrancePosition(void) { return m_vecEntrancePosition; }

	void						setRotation(float32 fRotation) { m_fRotation = fRotation; }
	float32						getRotation(void) { return m_fRotation; }

	void						setSize(bxcf::Vec2f& vecSize) { m_vecSize = vecSize; }
	bxcf::Vec2f&					getSize(void) { return m_vecSize; }

	void						setConstant8(uint32 uiConstant8) { m_uiConstant8 = uiConstant8; }
	uint32						getConstant8(void) { return m_uiConstant8; }

	void						setExitPosition(bxcf::Vec3f& vecExitPosition) { m_vecExitPosition = vecExitPosition; }
	bxcf::Vec3f&					getExitPosition(void) { return m_vecExitPosition; }

	void						setExitRotation(float32 fExitRotation) { m_fExitRotation = fExitRotation; }
	float32						getExitRotation(void) { return m_fExitRotation; }

	void						setTargetInterior(uint32 uiTargetInterior) { m_uiTargetInterior = uiTargetInterior; }
	uint32						getTargetInterior(void) { return m_uiTargetInterior; }

	void						setMarkerType(uint32 uiMarkerType) { m_uiMarkerType = uiMarkerType; }
	uint32						getMarkerType(void) { return m_uiMarkerType; }

	void						setInteriorName(std::string& strInteriorName) { m_strInteriorName = strInteriorName; }
	std::string&				getInteriorName(void) { return m_strInteriorName; }

	void						setSkyColourChanger(uint32 uiSkyColourChanger) { m_uiSkyColourChanger = uiSkyColourChanger; }
	uint32						getSkyColourChanger(void) { return m_uiSkyColourChanger; }

	void						setUnknown1(uint32 uiUnknown1) { m_uiUnknown1 = uiUnknown1; }
	uint32						getUnknown1(void) { return m_uiUnknown1; }

	void						setTimeOn(uint32 uiTimeOn) { m_uiTimeOn = uiTimeOn; }
	uint32						getTimeOn(void) { return m_uiTimeOn; }

	void						setTimeOff(uint32 uiTimeOff) { m_uiTimeOff = uiTimeOff; }
	uint32						getTimeOff(void) { return m_uiTimeOff; }

private:
	// GTA SA only
	bxcf::Vec3f					m_vecEntrancePosition;
	float32						m_fRotation;
	bxcf::Vec2f					m_vecSize;
	uint32						m_uiConstant8;
	bxcf::Vec3f					m_vecExitPosition;
	float32						m_fExitRotation; // in degrees
	uint32						m_uiTargetInterior;
	uint32						m_uiMarkerType;
	std::string					m_strInteriorName;
	uint32						m_uiSkyColourChanger;
	uint32						m_uiUnknown1;
	uint32						m_uiTimeOn;
	uint32						m_uiTimeOff;
};

#endif