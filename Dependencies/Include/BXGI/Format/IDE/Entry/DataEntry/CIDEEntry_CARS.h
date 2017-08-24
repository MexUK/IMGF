#ifndef CIDEEntry_CARS_H
#define CIDEEntry_CARS_H

#include "bxgi.h"
#include "Type/Types.h"
#include "Format/IDE/Entry/CIDEEntry_Data.h"
#include "Type/Vector/Vec2f.h"
#include <string>

class bxgi::CIDEEntry_CARS : public bxgi::CIDEEntry_Data
{
public:
	CIDEEntry_CARS(bxgi::CIDEFormat *pIDEFormat) :
		CIDEEntry_Data(pIDEFormat, IDE_SECTION_CARS),
		m_uiObjectId(0),
		m_uiSpawnFrequency(0),
		m_uiUnknown1(0),
		m_uiUnknown2(0),
		m_uiWheelModelId(0),
		m_fWheelScaleFront(0.0f),
		m_fWheelScaleRear(0.0f),
		m_fWheelScale(0.0f),
		m_uiUnknown3(0),
		m_uiMaxVehicleCountAtOneTime(0),
		m_vecWheelRadius{ 0.0f, 0.0f },
		m_fDirtLevel(0.0f),
		m_uiLODMultiplier(0),
		m_fSwankness(0.0f),
		m_uiFlags(0)
	{
	};

	void						unserialize(void);
	void						serialize(void);

	void						setObjectId(uint32 uiObjectId) { m_uiObjectId = uiObjectId; }
	uint32						getObjectId(void) { return m_uiObjectId; }

	void						setModelName(std::string& strModelName) { m_strModelName = strModelName; }
	std::string&				getModelName(void) { return m_strModelName; }

	void						setTXDName(std::string& strTXDName) { m_strTXDName = strTXDName; }
	std::string&				getTXDName(void) { return m_strTXDName; }

	void						setVehicleType(std::string& strVehicleType) { m_strVehicleType = strVehicleType; }
	std::string&				getVehicleType(void) { return m_strVehicleType; }

	void						setHandlingId(std::string& strHandlingId) { m_strHandlingId = strHandlingId; }
	std::string&				getHandlingId(void) { return m_strHandlingId; }

	void						setGameName(std::string& strGameName) { m_strGameName = strGameName; }
	std::string&				getGameName(void) { return m_strGameName; }

	void						setAnimationFile(std::string& strAnimationFile) { m_strAnimationFile = strAnimationFile; }
	std::string&				getAnimationFile(void) { return m_strAnimationFile; }

	void						setVehicleClass(std::string& strVehicleClass) { m_strVehicleClass = strVehicleClass; }
	std::string&				getVehicleClass(void) { return m_strVehicleClass; }

	void						setSpawnFrequency(uint32 uiSpawnFrequency) { m_uiSpawnFrequency = uiSpawnFrequency; }
	uint32						getSpawnFrequency(void) { return m_uiSpawnFrequency; }

	void						setUnknown1(uint32 uiUnknown1) { m_uiUnknown1 = uiUnknown1; }
	uint32						getUnknown1(void) { return m_uiUnknown1; }

	void						setUnknown2(uint32 uiUnknown2) { m_uiUnknown2 = uiUnknown2; }
	uint32						getUnknown2(void) { return m_uiUnknown2; }

	void						setWheelModelId(uint32 uiWheelModelId) { m_uiWheelModelId = uiWheelModelId; }
	uint32						getWheelModelId(void) { return m_uiWheelModelId; }

	void						setWheelScaleFront(float32 fWheelScaleFront) { m_fWheelScaleFront = fWheelScaleFront; }
	float32						getWheelScaleFront(void) { return m_fWheelScaleFront; }

	void						setWheelScaleRear(float32 fWheelScaleRear) { m_fWheelScaleRear = fWheelScaleRear; }
	float32						getWheelScaleRear(void) { return m_fWheelScaleRear; }

	void						setWheelScale(float32 fWheelScale) { m_fWheelScale = fWheelScale; }
	float32						getWheelScale(void) { return m_fWheelScale; }

	void						setUnknown3(uint32 uiUnknown3) { m_uiUnknown3 = uiUnknown3; }
	uint32						getUnknown3(void) { return m_uiUnknown3; }

	void						setAnimationFile2(std::string& strAnimationFile2) { m_strAnimationFile2 = strAnimationFile2; }
	std::string&				getAnimationFile2(void) { return m_strAnimationFile2; }

	void						setMaxVehicleCountAtOneTime(uint32 uiMaxVehicleCountAtOneTime) { m_uiMaxVehicleCountAtOneTime = uiMaxVehicleCountAtOneTime; }
	uint32						getMaxVehicleCountAtOneTime(void) { return m_uiMaxVehicleCountAtOneTime; }

	void						setWheelRadius(bxcf::Vec2f& vecWheelRadius) { m_vecWheelRadius = vecWheelRadius; }
	bxcf::Vec2f&					getWheelRadius(void) { return m_vecWheelRadius; }

	void						setDirtLevel(float32 fDirtLevel) { m_fDirtLevel = fDirtLevel; }
	float32						getDirtLevel(void) { return m_fDirtLevel; }

	void						setLODMultiplier(uint32 uiLODMultiplier) { m_uiLODMultiplier = uiLODMultiplier; }
	uint32						getLODMultiplier(void) { return m_uiLODMultiplier; }

	void						setSwankness(float32 fSwankness) { m_fSwankness = fSwankness; }
	float32						getSwankness(void) { return m_fSwankness; }

	void						setFlags(uint32 uiFlags) { m_uiFlags = uiFlags; }
	uint32						getFlags(void) { return m_uiFlags; }

private:
	// GTA III era & GTA IV
	std::string					m_strModelName;
	std::string					m_strTXDName;
	std::string					m_strVehicleType;
	std::string					m_strHandlingId;
	std::string					m_strGameName;
	std::string					m_strAnimationFile;
	uint32						m_uiSpawnFrequency;

	// GTA III era only
	uint32						m_uiObjectId;
	std::string					m_strVehicleClass;
	uint32						m_uiUnknown1;
	uint32						m_uiUnknown2;
	uint32						m_uiWheelModelId;
	float32						m_fWheelScaleFront;	// GTA SA only
	float32						m_fWheelScaleRear;	// GTA SA only
	float32						m_fWheelScale;		// GTA III & GTA VC only
	uint32						m_uiUnknown3;

	// GTA IV only
	std::string					m_strAnimationFile2;
	uint32						m_uiMaxVehicleCountAtOneTime;
	bxcf::Vec2f					m_vecWheelRadius;
	float32						m_fDirtLevel;
	uint32						m_uiLODMultiplier;
	float32						m_fSwankness;
	uint32						m_uiFlags;
};

#endif